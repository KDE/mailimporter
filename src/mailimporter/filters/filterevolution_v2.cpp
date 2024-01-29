/*
  filterevolution_v2.cpp  -  Evolution 2.0.x mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  Inspired and partly copied from filterevolution
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterevolution_v2.h"

#include <KLocalizedString>
#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;

/** Default constructor. */
FilterEvolution_v2::FilterEvolution_v2()
    : Filter(i18n("Import Evolution 2.x Local Mails and Folder Structure"),
             QStringLiteral("Danny Kukawka"),
             i18n("<p><b>Evolution 2.x import filter</b></p>"
                  "<p>Select the base directory of your local Evolution mailfolder (usually ~/.evolution/mail/local/).</p>"
                  "<p><b>Note:</b> Never choose a Folder which <u>does not</u> contain mbox-files (for example "
                  "a maildir): if you do, you will get many new folders.</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Evolution-Import\".</p>"))
{
}

/** Destructor. */
FilterEvolution_v2::~FilterEvolution_v2()
{
}

QString FilterEvolution_v2::isMailerFound()
{
    QDir directory(FilterEvolution_v2::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of evolution application", "Evolution (v2)");
    }
    return {};
}

QString FilterEvolution_v2::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/.evolution/mail/local");
}

/** Recursive import of Evolution's mboxes. */
void FilterEvolution_v2::import()
{
    clearCountDuplicate();
    /**
     * We ask the user to choose Evolution's root directory.
     * This should be usually ~/.evolution/mail/local/
     */
    QString evolDir = defaultSettingsPath();
    QDir d(evolDir);
    if (!d.exists()) {
        evolDir = QDir::homePath();
    }

    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), evolDir);
    if (!maildir.isEmpty()) {
        importMails(maildir);
    }
}

bool FilterEvolution_v2::excludeFiles(const QString &file)
{
    if ((file.endsWith(QLatin1StringView(".db")) || file.endsWith(QLatin1String(".cmeta")) || file.endsWith(QLatin1String(".ev-summary"))
         || file.endsWith(QLatin1StringView(".ibex.index")) || file.endsWith(QLatin1String(".ibex.index.data")))) {
        return true;
    }
    return false;
}

void FilterEvolution_v2::importMails(const QString &maildir)
{
    if (maildir.isEmpty()) {
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    setMailDir(maildir);
    /**
     * If the user only select homedir no import needed because
     * there should be no files and we surely import wrong files.
     */
    if (mailDir() == QDir::homePath() || mailDir() == (QDir::homePath() + QLatin1Char('/'))) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->setOverall(0);

        /** Recursive import of the MailArchives */
        QDir dir(mailDir());
        const QStringList rootSubDirs = dir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name); // Removal of . and ..
        int currentDir = 1;
        int numSubDirs = rootSubDirs.size();
        QStringList::ConstIterator endFilename(rootSubDirs.constEnd());
        for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != endFilename; ++filename, ++currentDir) {
            if (filterInfo()->shouldTerminate()) {
                break;
            }
            importDirContents(dir.filePath(*filename), *filename, *filename);
            filterInfo()->setOverall((int)((float)currentDir / numSubDirs * 100));
        }

        /** import last but not least all archives from the root-dir */
        QDir importDir(mailDir());
        const QStringList files = importDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Files, QDir::Name);
        endFilename = files.constEnd();
        for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != endFilename; ++mailFile) {
            if (filterInfo()->shouldTerminate()) {
                break;
            }
            QString temp_mailfile = *mailFile;
            if (!excludeFiles(temp_mailfile)) {
                filterInfo()->addInfoLogEntry(i18n("Start import file %1...", temp_mailfile));
                importMBox(mailDir() + temp_mailfile, temp_mailfile, QString());
            }
        }

        filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir()));
        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
        if (filterInfo()->shouldTerminate()) {
            filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
        }
    }
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

/**
 * Import of a directory contents.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 * @param KMailRootDir The directory's root directory in KMail's folder structure.
 * @param KMailSubDir The directory's direct ancestor in KMail's folder structure.
 */
void FilterEvolution_v2::importDirContents(const QString &dirName, const QString &KMailRootDir, const QString &KMailSubDir)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }

    /** Here Import all archives in the current dir */
    QDir dir(dirName);

    QDir importDir(dirName);
    const QStringList files = importDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Files, QDir::Name);
    QStringList::ConstIterator mailFileEnd(files.constEnd());
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != mailFileEnd; ++mailFile) {
        QString temp_mailfile = *mailFile;
        if (!excludeFiles(temp_mailfile)) {
            filterInfo()->addInfoLogEntry(i18n("Start import file %1...", temp_mailfile));
            importMBox((dirName + QLatin1Char('/') + temp_mailfile), KMailRootDir, KMailSubDir);
        }
    }

    /** If there are subfolders, we import them one by one */
    QDir subfolders(dirName);
    const QStringList subDirs = subfolders.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name);
    QStringList::ConstIterator end(subDirs.constEnd());
    for (QStringList::ConstIterator filename = subDirs.constBegin(); filename != end; ++filename) {
        QString kSubDir;
        if (!KMailSubDir.isNull()) {
            kSubDir = KMailSubDir + QLatin1Char('/') + *filename;
        } else {
            kSubDir = *filename;
        }
        importDirContents(subfolders.filePath(*filename), KMailRootDir, kSubDir);
    }
}

/**
 * Import of a MBox file.
 * @param info Information storage for the operation.
 * @param dirName The MBox's name.
 * @param KMailRootDir The directory's root directory in KMail's folder structure.
 * @param KMailSubDir The directory's equivalent in KMail's folder structure. *
 */
void FilterEvolution_v2::importMBox(const QString &mboxName, const QString &rootDir, const QString &targetDir)
{
    QFile mbox(mboxName);
    if (!mbox.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", mboxName));
    } else {
        bool first_msg = true;
        QFileInfo filenameInfo(mboxName);

        filterInfo()->setCurrent(0);
        if (mboxName.length() > 20) {
            QString tmp_info = mboxName;
            tmp_info.replace(mailDir(), QStringLiteral("../"));
            if (tmp_info.contains(QLatin1StringView(".sbd"))) {
                tmp_info.remove(QStringLiteral(".sbd"));
            }
            filterInfo()->setFrom(tmp_info);
        } else {
            filterInfo()->setFrom(mboxName);
        }

        if (targetDir.contains(QLatin1StringView(".sbd"))) {
            QString tmp_info = targetDir;
            tmp_info.remove(QStringLiteral(".sbd"));
            filterInfo()->setTo(tmp_info);
        } else {
            filterInfo()->setTo(targetDir);
        }

        QByteArray input(MAX_LINE, '\0');
        long l = 0;

        while (!mbox.atEnd()) {
            QTemporaryFile tmp;
            tmp.open();
            /** @todo check if the file is really a mbox, maybe search for 'from' string at start */
            /* comment by Danny:
             * Don't use QTextStream to read from mbox, better use QDataStream. QTextStream only
             * support Unicode/Latin1/Locale. So you lost information from emails with
             * charset!=Unicode/Latin1/Locale (e.g. KOI8-R) and Content-Transfer-Encoding != base64
             * (e.g. 8Bit). It also not help to convert the QTextStream to Unicode. By this you
             * get Unicode/UTF-email but KMail can't detect the correct charset.
             */
            QByteArray separate;

            if (!first_msg) {
                tmp.write(input.constData(), l);
            }
            l = mbox.readLine(input.data(), MAX_LINE); // read the first line, prevent "From "
            tmp.write(input.constData(), l);

            while (!mbox.atEnd() && (l = mbox.readLine(input.data(), MAX_LINE)) && ((separate = input.data()).left(5) != "From ")) {
                tmp.write(input.constData(), l);
            }
            tmp.flush();
            first_msg = false;

            QString destFolder;
            QString _targetDir = targetDir;
            if (!targetDir.isNull()) {
                if (_targetDir.contains(QLatin1StringView(".sbd"))) {
                    _targetDir.remove(QStringLiteral(".sbd"));
                }
                destFolder += QStringLiteral("Evolution-Import/") + _targetDir + QLatin1Char('/') + filenameInfo.completeBaseName(); // mboxName;
            } else {
                destFolder = QStringLiteral("Evolution-Import/") + rootDir;
                if (destFolder.contains(QLatin1StringView(".sbd"))) {
                    destFolder.remove(QStringLiteral(".sbd"));
                }
            }

            if (!importMessage(destFolder, tmp.fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
            }

            int currentPercentage = (int)(((float)mbox.pos() / filenameInfo.size()) * 100);
            filterInfo()->setCurrent(currentPercentage);
            if (filterInfo()->shouldTerminate()) {
                break;
            }
        }
        mbox.close();
    }
}

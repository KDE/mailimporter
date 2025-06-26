/*
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterevolution.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;

/** Default constructor. */
FilterEvolution::FilterEvolution()
    : Filter(i18n("Import Evolution 1.x Local Mails and Folder Structure"),
             i18n("Simon MARTIN<br /><br />( Filter accelerated by Danny Kukawka )"),
             i18n("<p><b>Evolution 1.x import filter</b></p>"
                  "<p>Select the base directory of Evolution's mails (usually ~/evolution/local).</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Evolution-Import\".</p>"))
{
}

/** Destructor. */
FilterEvolution::~FilterEvolution()
{
}

QString FilterEvolution::isMailerFound()
{
    QDir directory(FilterEvolution::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of evolution application", "Evolution");
    }
    return {};
}

QString FilterEvolution::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/evolution/local");
}

/** Recursive import of Evolution's mboxes. */
void FilterEvolution::import()
{
    // We ask the user to choose Evolution's root directory.
    QString evolDir = defaultSettingsPath();
    QDir d(evolDir);
    if (!d.exists()) {
        evolDir = QDir::homePath();
    }
    importMails(QFileDialog::getExistingDirectory(filterInfo()->parentWidget(), QString(), evolDir));
}

void FilterEvolution::importMails(const QString &maildir)
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
    if (mailDir() == QDir::homePath() || mailDir() == (QDir::homePath() + u'/')) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->setOverall(0);
        // Recursive import of the MBoxes.
        QDir dir(mailDir());
        const QStringList rootSubDirs = dir.entryList(QStringList(u"[^\\.]*"_s), QDir::Dirs, QDir::Name); // Removal of . and ..
        int currentDir = 1;
        int numSubDirs = rootSubDirs.size();
        QStringList::ConstIterator end(rootSubDirs.constEnd());
        for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename, ++currentDir) {
            importDirContents(dir.filePath(*filename), *filename, QString());
            filterInfo()->setOverall((int)((float)currentDir / numSubDirs * 100));
        }
    }
    filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir()));
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
void FilterEvolution::importDirContents(const QString &dirName, const QString &KMailRootDir, const QString &KMailSubDir)
{
    // If there is a mbox, we import it
    QDir dir(dirName);
    if (dir.exists(u"mbox"_s)) {
        importMBox(dirName + QLatin1StringView("/mbox"), KMailRootDir, KMailSubDir);
    }
    // If there are subfolders, we import them one by one
    if (dir.exists(u"subfolders"_s)) {
        QDir subfolders(dirName + QLatin1StringView("/subfolders"));
        const QStringList subDirs = subfolders.entryList(QStringList(u"[^\\.]*"_s), QDir::Dirs, QDir::Name);
        QStringList::ConstIterator end(subDirs.constEnd());

        for (QStringList::ConstIterator filename = subDirs.constBegin(); filename != end; ++filename) {
            QString kSubDir;
            if (!KMailSubDir.isNull()) {
                kSubDir = KMailSubDir + u'/' + *filename;
            } else {
                kSubDir = *filename;
            }
            importDirContents(subfolders.filePath(*filename), KMailRootDir, kSubDir);
        }
    }
}

/**
 * Import of a MBox file.
 * @param info Information storage for the operation.
 * @param dirName The MBox's name.
 * @param KMailRootDir The directory's root directory in KMail's folder structure.
 * @param KMailSubDir The directory's equivalent in KMail's folder structure. *
 */
void FilterEvolution::importMBox(const QString &mboxName, const QString &rootDir, const QString &targetDir)
{
    QFile mbox(mboxName);
    QString tmp_from = mboxName;
    if (!mbox.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", mboxName));
    } else {
        bool first_msg = true;
        QFileInfo filenameInfo(mboxName);

        filterInfo()->setCurrent(0);
        if (mboxName.length() > 20) {
            QString tmp_info = mboxName;
            tmp_info.replace(mailDir(), u".."_s);
            if (tmp_info.contains(QLatin1StringView("subfolders/"))) {
                tmp_info.remove(u"subfolders/"_s);
            }
            filterInfo()->setFrom(tmp_info);
            tmp_from = tmp_info;
        } else {
            filterInfo()->setFrom(mboxName);
        }
        if (targetDir.contains(QLatin1StringView("subfolders/"))) {
            QString tmp_info = targetDir;
            tmp_info.remove(u"subfolders/"_s);
            filterInfo()->setTo(tmp_info);
        } else {
            filterInfo()->setTo(targetDir);
        }

        filterInfo()->addInfoLogEntry(i18n("Importing emails from %1...", tmp_from));

        QByteArray input(MAX_LINE, '\0');
        long l = 0;

        while (!mbox.atEnd()) {
            QTemporaryFile tmp;
            tmp.open();
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

            QString destFolder = rootDir;
            if (!targetDir.isNull()) {
                destFolder = QLatin1StringView("Evolution-Import/") + destFolder + u'/' + targetDir;
            } else {
                destFolder = QLatin1StringView("Evolution-Import/") + destFolder;
            }

            if (!importMessage(destFolder, tmp.fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
            }

            const int currentPercentage = (int)(((float)mbox.pos() / filenameInfo.size()) * 100);
            filterInfo()->setCurrent(currentPercentage);
            if (filterInfo()->shouldTerminate()) {
                return;
            }
        }

        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
        clearCountDuplicate();
        mbox.close();
    }
}

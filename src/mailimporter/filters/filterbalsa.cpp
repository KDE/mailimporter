/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterbalsa.h"

#include <KLocalizedString>
#include <QFileDialog>

using namespace MailImporter;

class MailImporter::FilterBalsaPrivate
{
public:
    int mImportDirDone = 0;
    int mTotalDir = 0;
};
/** Default constructor. */
FilterBalsa::FilterBalsa()
    : Filter(i18n("Import Balsa Local Mails and Folder Structure"),
             QStringLiteral("Laurent Montel"),
             i18n("<p><b>Balsa import filter</b></p>"
                  "<p>Select the base directory of your local Balsa mailfolder (usually ~/mail/).</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Balsa-Import\".</p>"))
    , d(new MailImporter::FilterBalsaPrivate)
{
}

/** Destructor. */
FilterBalsa::~FilterBalsa()
{
    delete d;
}

QString FilterBalsa::isMailerFound()
{
    QDir directory(FilterBalsa::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of balsa application", "Balsa");
    }
    return {};
}

QString FilterBalsa::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1String("/.balsa/");
}

QString FilterBalsa::localMailDirPath()
{
    return QDir::homePath() + QLatin1String("/mail/");
}

/** Recursive import of KMail maildir. */
void FilterBalsa::import()
{
    clearCountDuplicate();
    QString balsaDir = localMailDirPath();
    QDir d(balsaDir);
    if (!d.exists()) {
        balsaDir = QDir::homePath();
    }
    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), balsaDir);
    importMails(maildir);
}

void FilterBalsa::processDirectory(const QString &path)
{
    QDir dir(path);
    const QStringList rootSubDirs = dir.entryList(QStringList(QStringLiteral("*")), QDir::Dirs | QDir::Hidden, QDir::Name);
    QStringList::ConstIterator end = rootSubDirs.constEnd();
    for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        if (!(*filename == QLatin1Char('.') || *filename == QLatin1String(".."))) {
            filterInfo()->setCurrent(0);
            importDirContents(dir.filePath(*filename));
            filterInfo()->setOverall((d->mTotalDir > 0) ? (int)((float)d->mImportDirDone / d->mTotalDir * 100) : 0);
            filterInfo()->setCurrent(100);
        }
    }
}

void FilterBalsa::importMails(const QString &maildir)
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
        d->mImportDirDone = 0;

        /** Recursive import of the MailArchives */
        QDir dir(mailDir());
        d->mTotalDir = Filter::countDirectory(dir, true /*search hidden directory*/);

        processDirectory(mailDir());

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
 */
void FilterBalsa::importDirContents(const QString &dirName)
{
    /** Here Import all archives in the current dir */
    importFiles(dirName);

    /** If there are subfolders, we import them one by one */
    processDirectory(dirName);
}

/**
 * Import the files within a Folder.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 */
void FilterBalsa::importFiles(const QString &dirName)
{
    QDir dir(dirName);
    QString _path;
    bool generatedPath = false;

    QDir importDir(dirName);
    const QStringList files = importDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Files, QDir::Name);
    int currentFile = 1, numFiles = files.size();
    QStringList::ConstIterator filesEnd(files.constEnd());

    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != filesEnd; ++mailFile, ++currentFile) {
        if (filterInfo()->shouldTerminate()) {
            return;
        }
        QString temp_mailfile = *mailFile;
        if (!(temp_mailfile.endsWith(QLatin1String(".db")) || temp_mailfile.endsWith(QLatin1String(".cmeta"))
              || temp_mailfile.endsWith(QLatin1String(".ev-summary")) || temp_mailfile.endsWith(QLatin1String(".ibex.index"))
              || temp_mailfile.endsWith(QLatin1String(".ibex.index.data")))) {
            if (!generatedPath) {
                _path = i18nc("define folder name where we import evolution mails", "Evolution-Import");
                QString _tmp = dir.filePath(*mailFile);
                _tmp.remove(mailDir(), Qt::CaseSensitive);
                QStringList subFList = _tmp.split(QLatin1Char('/'), Qt::SkipEmptyParts);
                QStringList::ConstIterator end(subFList.end());
                for (QStringList::ConstIterator it = subFList.constBegin(); it != end; ++it) {
                    QString _cat = *it;
                    if (!(_cat == *mailFile)) {
                        if (_cat.startsWith(QLatin1Char('.'))) {
                            _cat.remove(0, 1);
                        }
                        // Evolution store inbox as "."
                        if (_cat.startsWith(QLatin1Char('.'))) {
                            _cat.replace(0, 1, QStringLiteral("Inbox/"));
                        }

                        _path += QLatin1Char('/') + _cat;
                        _path.replace(QLatin1Char('.'), QLatin1Char('/'));
                    }
                }
                if (_path.endsWith(QLatin1String("cur"))) {
                    _path.remove(_path.length() - 4, 4);
                }
                QString _info = _path;
                filterInfo()->addInfoLogEntry(i18n("Import folder %1...", _info));
                filterInfo()->setFrom(_info);
                filterInfo()->setTo(_path);
                generatedPath = true;
            }
            const MailImporter::MessageStatus status = statusFromFile(*mailFile);

            if (!importMessage(_path, dir.filePath(*mailFile), filterInfo()->removeDupMessage(), status)) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", *mailFile));
            }
            filterInfo()->setCurrent((int)((float)currentFile / numFiles * 100));
        }
    }
}

MailImporter::MessageStatus FilterBalsa::statusFromFile(const QString &filename)
{
    MailImporter::MessageStatus status;
    const int statusIndex = filename.indexOf(QLatin1String(":2,"));
    if (statusIndex != -1) {
        const QString statusStr = filename.right(filename.length() - statusIndex - 3);
        if (statusStr.contains(QLatin1Char('S'))) {
            status.setRead(true);
        }
        if (statusStr.contains(QLatin1Char('F'))) {
            // TODO
        }
        if (statusStr.contains(QLatin1Char('R'))) {
            status.setReplied(true);
        }
        if (statusStr.contains(QLatin1Char('P'))) {
            status.setForwarded(true);
        }
    }
    return status;
}

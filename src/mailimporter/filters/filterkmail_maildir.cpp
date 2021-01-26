/*
  filterkmail_maildir.cpp  -  Kmail maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterkmail_maildir.h"

#include <KLocalizedString>
#include <QFileDialog>

using namespace MailImporter;

class MailImporter::FilterKMail_maildirPrivate
{
public:
    int mImportDirDone = 0;
    int mTotalDir = 0;
};

/** Default constructor. */
FilterKMail_maildir::FilterKMail_maildir()
    : Filter(i18n("Import KMail Maildirs and Folder Structure"),
             QStringLiteral("Danny Kukawka"),
             i18n("<p><b>KMail import filter</b></p>"
                  "<p>Select the base directory of the KMail mailfolder you want to import.</p>"
                  "<p><b>Note:</b> Never select your current local KMail maildir (usually "
                  "~/Mail or ~/.kde/share/apps/kmail/mail ): in this case, ImportWizard may become stuck "
                  "in a continuous loop. </p>"
                  "<p>This filter does not import KMail mailfolders with mbox files.</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"KMail-Import\" in your local folder.</p>"))
    , d(new MailImporter::FilterKMail_maildirPrivate)
{
}

/** Destructor. */
FilterKMail_maildir::~FilterKMail_maildir()
{
    delete d;
}

/** Recursive import of KMail maildir. */
void FilterKMail_maildir::import()
{
    clearCountDuplicate();
    const QString homeDir = QDir::homePath();
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), homeDir);
    if (!maildir.isEmpty()) {
        importMails(maildir);
    }
}

void FilterKMail_maildir::processDirectory(const QString &path)
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
            ++d->mImportDirDone;
        }
    }
}

void FilterKMail_maildir::importMails(const QString &maildir)
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
    }
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

/**
 * Import of a directory contents.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 */
void FilterKMail_maildir::importDirContents(const QString &dirName)
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
void FilterKMail_maildir::importFiles(const QString &dirName)
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
        if (!(temp_mailfile.endsWith(QLatin1String(".index")) || temp_mailfile.endsWith(QLatin1String(".index.ids"))
              || temp_mailfile.endsWith(QLatin1String(".index.sorted")) || temp_mailfile.endsWith(QLatin1String(".uidcache")))) {
            if (!generatedPath) {
                _path = QStringLiteral("KMail-Import");
                QString _tmp = dir.filePath(*mailFile);
                _tmp.remove(mailDir(), Qt::CaseSensitive);
                const QStringList subFList = _tmp.split(QLatin1Char('/'), Qt::SkipEmptyParts);
                QStringList::ConstIterator end(subFList.end());
                for (QStringList::ConstIterator it = subFList.constBegin(); it != end; ++it) {
                    QString _cat = *it;
                    if (!(_cat == *mailFile)) {
                        if (_cat.startsWith(QLatin1Char('.')) && _cat.endsWith(QLatin1String(".directory"))) {
                            _cat.remove(0, 1);
                            _cat.remove((_cat.length() - 10), 10);
                        } else if (_cat.startsWith(QLatin1Char('.'))) {
                            _cat.remove(0, 1);
                        }
                        _path += QLatin1Char('/') + _cat;
                    }
                }
                if (_path.endsWith(QLatin1String("cur"))) {
                    _path.remove(_path.length() - 4, 4);
                }
                QString _info = _path;
                filterInfo()->addInfoLogEntry(i18n("Import folder %1...", _info.remove(0, 12)));
                filterInfo()->setFrom(_info);
                filterInfo()->setTo(_path);
                generatedPath = true;
            }

            if (!importMessage(_path, dir.filePath(*mailFile), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1, duplicated message", *mailFile));
            }
            filterInfo()->setCurrent((int)((float)currentFile / numFiles * 100));
        }
    }
}

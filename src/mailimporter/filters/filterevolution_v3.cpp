/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterevolution_v3.h"
using namespace Qt::Literals::StringLiterals;


#include <KLocalizedString>
#include <QFileDialog>

using namespace MailImporter;

class MailImporter::FilterEvolution_v3Private
{
public:
    int mImportDirDone = -1;
    int mTotalDir = -1;
};
/** Default constructor. */
FilterEvolution_v3::FilterEvolution_v3()
    : Filter(i18n("Import Evolution 3.x Local Mails and Folder Structure"),
             u"Laurent Montel"_s,
             i18n("<p><b>Evolution 3.x import filter</b></p>"
                  "<p>Select the base directory of your local Evolution mailfolder (usually ~/.local/share/evolution/mail/local/).</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Evolution-Import\".</p>"))
    , d(new MailImporter::FilterEvolution_v3Private)
{
}

/** Destructor. */
FilterEvolution_v3::~FilterEvolution_v3() = default;

QString FilterEvolution_v3::isMailerFound()
{
    QDir directory(FilterEvolution_v3::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of evolution application", "Evolution (v3)");
    }
    return {};
}

QString FilterEvolution_v3::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/.local/share/evolution/mail/local/");
}

/** Recursive import of KMail maildir. */
void FilterEvolution_v3::import()
{
    clearCountDuplicate();
    QString evolDir = defaultSettingsPath();
    QDir d(evolDir);
    if (!d.exists()) {
        evolDir = QDir::homePath();
    }

    const QString dir = QFileDialog::getExistingDirectory(nullptr, QString(), evolDir);
    if (!dir.isEmpty()) {
        importMails(dir);
    }
}

void FilterEvolution_v3::processDirectory(const QString &path)
{
    QDir dir(path);
    const QStringList rootSubDirs = dir.entryList(QStringList(u"*"_s), QDir::Dirs | QDir::Hidden, QDir::Name);
    QStringList::ConstIterator end = rootSubDirs.constEnd();
    for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        if (!(*filename == u'.' || *filename == QLatin1StringView(".."))) {
            filterInfo()->setCurrent(0);
            importDirContents(dir.filePath(*filename));
            filterInfo()->setOverall((d->mTotalDir > 0) ? (int)((float)d->mImportDirDone / d->mTotalDir * 100) : 0);
            filterInfo()->setCurrent(100);
        }
    }
}

void FilterEvolution_v3::importMails(const QString &maildir)
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
void FilterEvolution_v3::importDirContents(const QString &dirName)
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
void FilterEvolution_v3::importFiles(const QString &dirName)
{
    QDir dir(dirName);
    QString _path;
    bool generatedPath = false;

    QDir importDir(dirName);
    const QStringList files = importDir.entryList(QStringList(u"[^\\.]*"_s), QDir::Files, QDir::Name);
    int currentFile = 1;
    int numFiles = files.size();
    QStringList::ConstIterator filesEnd(files.constEnd());

    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != filesEnd; ++mailFile, ++currentFile) {
        if (filterInfo()->shouldTerminate()) {
            return;
        }
        QString temp_mailfile = *mailFile;
        if (!(temp_mailfile.endsWith(QLatin1StringView(".db")) || temp_mailfile.endsWith(QLatin1StringView(".cmeta"))
              || temp_mailfile.endsWith(QLatin1StringView(".ev-summary")) || temp_mailfile.endsWith(QLatin1StringView(".ibex.index"))
              || temp_mailfile.endsWith(QLatin1StringView(".ibex.index.data")))) {
            if (!generatedPath) {
                _path = i18nc("define folder name where we import evolution mails", "Evolution-Import");
                QString _tmp = dir.filePath(*mailFile);
                _tmp.remove(mailDir(), Qt::CaseSensitive);
                QStringList subFList = _tmp.split(u'/', Qt::SkipEmptyParts);
                QStringList::ConstIterator end(subFList.end());
                for (QStringList::ConstIterator it = subFList.constBegin(); it != end; ++it) {
                    QString _cat = *it;
                    if (!(_cat == *mailFile)) {
                        if (_cat.startsWith(u'.')) {
                            _cat.remove(0, 1);
                        }
                        // Evolution store inbox as "."
                        if (_cat.startsWith(u'.')) {
                            _cat.replace(0, 1, u"Inbox/"_s);
                        }

                        _path += u'/' + _cat;
                        _path.replace(u'.', u'/');
                    }
                }
                if (_path.endsWith(QLatin1StringView("cur"))) {
                    _path.remove(_path.length() - 4, 4);
                }
                QString _info = _path;
                filterInfo()->addInfoLogEntry(i18n("Import folder %1...", _info));
                filterInfo()->setFrom(_info);
                filterInfo()->setTo(_path);
                generatedPath = true;
            }
            MailImporter::MessageStatus status = statusFromFile(*mailFile);

            if (!importMessage(_path, dir.filePath(*mailFile), filterInfo()->removeDupMessage(), status)) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", *mailFile));
            }
            filterInfo()->setCurrent((int)((float)currentFile / numFiles * 100));
        }
    }
}

MailImporter::MessageStatus FilterEvolution_v3::statusFromFile(const QString &filename)
{
    MailImporter::MessageStatus status;
    const int statusIndex = filename.indexOf(QLatin1StringView(":2,"));
    if (statusIndex != -1) {
        const QString statusStr = filename.right(filename.length() - statusIndex - 3);
        if (statusStr.contains(u'S')) {
            status.setRead(true);
        }
        if (statusStr.contains(u'F')) {
            // TODO ?
        }
        if (statusStr.contains(u'R')) {
            status.setReplied(true);
        }
        if (statusStr.contains(u'P')) {
            status.setForwarded(true);
        }
    }
    return status;
}

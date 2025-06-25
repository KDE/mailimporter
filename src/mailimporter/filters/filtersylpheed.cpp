/*
  filtersylpheed.cpp  -  Sylpheed maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filtersylpheed.h"
using namespace Qt::Literals::StringLiterals;


#include "mailimporter_debug.h"
#include <KLocalizedString>
#include <QDomDocument>
#include <QDomElement>
#include <QFileDialog>

using namespace MailImporter;

class MailImporter::FilterSylpheedPrivate
{
public:
    int mImportDirDone = 0;
    int mTotalDir = 0;
};
/** Default constructor. */
FilterSylpheed::FilterSylpheed()
    : Filter(i18n("Import Sylpheed Maildirs and Folder Structure"),
             u"Danny Kukawka"_s,
             i18n("<p><b>Sylpheed import filter</b></p>"
                  "<p>Select the base directory of the Sylpheed mailfolder you want to import "
                  "(usually: ~/Mail ).</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Sylpheed-Import\" in your local folder.</p>"
                  "<p>This filter also recreates the status of message, e.g. new or forwarded.</p>"))
    , d(new MailImporter::FilterSylpheedPrivate)
{
}

/** Destructor. */
FilterSylpheed::~FilterSylpheed() = default;

QString FilterSylpheed::isMailerFound()
{
    QDir directory(FilterSylpheed::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of sylpheed application", "Sylpheed");
    }
    return {};
}

QString FilterSylpheed::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/.sylpheed-2.0/");
}

QString FilterSylpheed::localMailDirPath()
{
    QFile folderListFile(FilterSylpheed::defaultSettingsPath() + QLatin1StringView("/folderlist.xml"));
    if (folderListFile.exists()) {
        QDomDocument doc;
        if (!folderListFile.open(QIODevice::ReadOnly)) {
            qCWarning(MAILIMPORTER_LOG) << "Impossible to open " << folderListFile.fileName();
        }
        const QDomDocument::ParseResult parseResult = doc.setContent(&folderListFile);
        if (!parseResult) {
            qCDebug(MAILIMPORTER_LOG) << "Unable to load document.Parse error in line " << parseResult.errorLine << ", col " << parseResult.errorColumn << ": "
                                      << qPrintable(parseResult.errorMessage);
            return QString();
        }
        const QDomElement settings = doc.documentElement();

        if (settings.isNull()) {
            return QString();
        }

        for (QDomElement e = settings.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
            if (e.tagName() == QLatin1StringView("folder")) {
                if (e.hasAttribute(u"type"_s)) {
                    if (e.attribute(u"type"_s) == QLatin1StringView("mh")) {
                        return e.attribute(u"path"_s);
                    }
                }
            }
        }
    }
    return QString();
}

/** Recursive import of Sylpheed maildir. */
void FilterSylpheed::import()
{
    QString homeDir = localMailDirPath();
    if (homeDir.isEmpty()) {
        homeDir = QDir::homePath();
    }
    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), homeDir);
    if (!maildir.isEmpty()) {
        importMails(maildir);
    }
}

void FilterSylpheed::processDirectory(const QString &path)
{
    QDir dir(path);
    const QStringList rootSubDirs = dir.entryList(QStringList(u"[^\\.]*"_s), QDir::Dirs, QDir::Name);
    QStringList::ConstIterator end = rootSubDirs.constEnd();
    for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        importDirContents(dir.filePath(*filename));
        filterInfo()->setOverall((d->mTotalDir > 0) ? (int)((float)d->mImportDirDone / d->mTotalDir * 100) : 0);
        ++d->mImportDirDone;
    }
}

void FilterSylpheed::importMails(const QString &maildir)
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

        /** Recursive import of the MailFolders */
        QDir dir(mailDir());

        d->mTotalDir = Filter::countDirectory(dir, false);
        processDirectory(mailDir());

        filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir()));
        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
    }
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }
    clearCountDuplicate();
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

/**
 * Import of a directory contents.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 */
void FilterSylpheed::importDirContents(const QString &dirName)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }

    /** Here Import all archives in the current dir */
    importFiles(dirName);

    /** If there are subfolders, we import them one by one */
    processDirectory(dirName);
}

bool FilterSylpheed::excludeFile(const QString &file)
{
    if (file.endsWith(QLatin1StringView(".sylpheed_cache")) || file.endsWith(QLatin1StringView(".sylpheed_mark"))
        || file.endsWith(QLatin1StringView(".mh_sequences"))) {
        return true;
    }
    return false;
}

QString FilterSylpheed::defaultInstallFolder() const
{
    return i18nc("define folder name where we will import sylpheed mails", "Sylpheed-Import") + u'/';
}

QString FilterSylpheed::markFile() const
{
    return u".sylpheed_mark"_s;
}

/**
 * Import the files within a Folder.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 */
void FilterSylpheed::importFiles(const QString &dirName)
{
    QDir dir(dirName);
    QString _path;
    bool generatedPath = false;

    QHash<QString, unsigned long> msgflags;

    QDir importDir(dirName);
    const QString defaultInstallPath = defaultInstallFolder();

    const QStringList files = importDir.entryList(QStringList(u"[^\\.]*"_s), QDir::Files, QDir::Name);
    int currentFile = 1;
    int numFiles = files.size();

    readMarkFile(dir.filePath(markFile()), msgflags);

    QStringList::ConstIterator end(files.constEnd());
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile, ++currentFile) {
        if (filterInfo()->shouldTerminate()) {
            return;
        }
        QString _mfile = *mailFile;
        if (!excludeFile(_mfile)) {
            if (!generatedPath) {
                _path = defaultInstallPath;
                QString _tmp = dir.filePath(*mailFile);
                _tmp.remove(_tmp.length() - _mfile.length() - 1, _mfile.length() + 1);
                _path += _tmp.remove(mailDir(), Qt::CaseSensitive);
                QString _info = _path;
                filterInfo()->addInfoLogEntry(i18n("Import folder %1...", _info.remove(0, 15)));

                filterInfo()->setFrom(_info);
                filterInfo()->setTo(_path);
                generatedPath = true;
            }

            MailImporter::MessageStatus status;
            if (msgflags[_mfile]) {
                status = msgFlagsToString((msgflags[_mfile]));
            } else {
                status.setRead(true); // 0 == read
            }
            if (!importMessage(_path, dir.filePath(*mailFile), filterInfo()->removeDupMessage(), status)) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", *mailFile));
            }
            filterInfo()->setCurrent((int)((float)currentFile / numFiles * 100));
        }
    }
}

void FilterSylpheed::readMarkFile(const QString &path, QHash<QString, unsigned long> &dict)
{
    /* Each sylpheed mail directory contains a .sylpheed_mark file which
     * contains all the flags for each messages. The layout of this file
     * is documented in the source code of sylpheed: in procmsg.h for
     * the flag bits, and procmsg.c.
     *
     * Note that the mark file stores 32 bit unsigned integers in the
     * platform's native "endianness".
     *
     * The mark file starts with a 32 bit unsigned integer with a version
     * number. It is then followed by pairs of 32 bit unsigned integers,
     * the first one with the message file name (which is a number),
     * and the second one with the actual message flags */

    quint32 in;
    quint32 flags;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream stream(&file);

    if (Q_BYTE_ORDER == Q_LITTLE_ENDIAN) {
        stream.setByteOrder(QDataStream::LittleEndian);
    }

    /* Read version; if the value is reasonably too big, we're looking
     * at a file created on another platform. I don't have any test
     * marks/folders, so just ignoring this case */
    stream >> in;
    if (in > (quint32)0xffff) {
        return;
    }

    while (!stream.atEnd()) {
        if (filterInfo()->shouldTerminate()) {
            file.close();
            return;
        }
        stream >> in;
        stream >> flags;
        QString s;
        s.setNum((uint)in);
        dict.insert(s, flags);
    }
}

MailImporter::MessageStatus FilterSylpheed::msgFlagsToString(unsigned long flags)
{
    MailImporter::MessageStatus status;
    /* see sylpheed's procmsg.h */
    if (flags & 2UL) {
        status.setRead(false);
    }
    if ((flags & 3UL) == 0UL) {
        status.setRead(true);
    }
    if (flags & 8UL) {
        status.setDeleted(true);
    }
    if (flags & 16UL) {
        status.setReplied(true);
    }
    if (flags & 32UL) {
        status.setForwarded(true);
    }
    return status;
}

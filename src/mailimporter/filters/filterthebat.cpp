/*
  filterthebat.cpp  -  TheBat! mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterthebat.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QFileDialog>
#include <QRegularExpression>
#include <QTemporaryFile>

using namespace MailImporter;

class MailImporter::FilterTheBatPrivate
{
public:
    int mImportDirDone = 0;
    int mTotalDir = 0;
};

/** Default constructor. */
FilterTheBat::FilterTheBat()
    : Filter(i18n("Import The Bat! Mails and Folder Structure"),
             u"Danny Kukawka"_s,
             i18n("<p><b>The Bat! import filter</b></p>"
                  "<p>Select the base directory of the \'The Bat!\' local mailfolder you "
                  "want to import.</p>"
                  "<p><b>Note:</b> This filter imports the *.tbb-files from \'The Bat!\' "
                  "local folder, e.g. from POP accounts, and not from IMAP/DIMAP accounts.</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"TheBat-Import\" in your local account.</p>"))
    , d(new MailImporter::FilterTheBatPrivate)
{
}

/** Destructor. */
FilterTheBat::~FilterTheBat() = default;

/** Recursive import of The Bat! maildir. */
void FilterTheBat::import()
{
    const QString _homeDir = QDir::homePath();
    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), _homeDir);
    if (!maildir.isEmpty()) {
        importMails(maildir);
    }
}

void FilterTheBat::processDirectory(const QString &path)
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

void FilterTheBat::importMails(const QString &maildir)
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
void FilterTheBat::importDirContents(const QString &dirName)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }

    /** Here Import all archives in the current dir */
    QDir importDir(dirName);
    const QStringList files = importDir.entryList(QStringList(u"*.[tT][bB][bB]"_s), QDir::Files, QDir::Name);
    QStringList::ConstIterator end = files.constEnd();
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
        QString temp_mailfile = *mailFile;
        importFiles((dirName + u'/' + temp_mailfile));
        if (filterInfo()->shouldTerminate()) {
            return;
        }
    }

    /** If there are subfolders, we import them one by one */
    processDirectory(dirName);
}

/**
 * Import the files within a Folder.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 */
void FilterTheBat::importFiles(const QString &FileName)
{
    // Format of a tbb-file from The Bat! 3.x
    // ----------------------------------------
    // First comes a header of 3K (3128 byte/ 0x00000c38), which we can forget.
    // The byte 3129 is the first character of the first message.
    //
    // The end of a message is marked through "! p 0" and 43 following characters.
    // (within: "_UB", blanks and some other chars.) Together are 48 characters as
    // separator.
    // ----------------------------------------

    long l = 0;
    QByteArray input(50, '\0');
    const QRegularExpression regexp(u"!.p.0"_s);
    QFile tbb(FileName);
    int iFound = 0;
    int count = 0;
    QList<long> offsets;

    if (!tbb.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", FileName));
    } else {
        // BUILD the index of messages :
        // We need this really ugly way, because read with tbb.readLine()
        // does not work correct. Maybe in come in a continuous loop !!!
        // Reason:
        //      if you use readLine() to read from a file with binary data
        //      QFile::at() and QFile::atEnd() return wrong value. So we
        //      never get QFile::atEnd() == true in some cases. This looks
        //      like a bug in Qt3 maybe fixed in Qt4.
        //
        while ((l = tbb.read(input.data(), 50))) {
            if (filterInfo()->shouldTerminate()) {
                tbb.close();
                return;
            }
            QString _tmp = QString::fromUtf8(input.data());

            if (tbb.atEnd()) {
                break;
            }

            iFound = _tmp.count(regexp);
            if (!iFound) {
                iFound = _tmp.lastIndexOf(u'!');
                if (iFound >= 0 && ((l - iFound) < 5)) {
                    int _i = tbb.pos();
                    tbb.seek((_i - iFound));
                }
            } else {
                ++count;
                const long endOfEmail = (tbb.pos() - l + _tmp.indexOf(regexp));
                offsets.append(endOfEmail);
            }
        }

        // IMPORT the messages:
        if (!offsets.empty() || (offsets.empty() && (tbb.size() > 3128))) {
            offsets.append(tbb.size());
            tbb.seek(3128);
            long lastPos = 3128;
            long endPos = 0;

            QString _path = i18nc("Define folder where we will import thebat mails", "TheBat-Import") + u'/';
            QString _tmp = FileName;
            _tmp.remove(_tmp.length() - 13, 13);
            _path += _tmp.remove(mailDir(), Qt::CaseSensitive);
            QString _info = _path;
            filterInfo()->addInfoLogEntry(i18n("Import folder %1...", _info.remove(0, 14)));
            filterInfo()->setTo(_path);
            filterInfo()->setFrom(QLatin1StringView("../") + _info + QLatin1StringView("/messages.tbb"));

            QList<long>::Iterator end = offsets.end();
            for (QList<long>::Iterator it = offsets.begin(); it != end; ++it) {
                if (filterInfo()->shouldTerminate()) {
                    tbb.close();
                    return;
                }
                endPos = *it;
                QByteArray input(endPos - lastPos, '\0');
                tbb.read(input.data(), endPos - lastPos);

                QTemporaryFile tmp;
                tmp.open();
                tmp.write(input.constData(), endPos - lastPos);
                tmp.flush();

                if (!importMessage(_path, tmp.fileName(), filterInfo()->removeDupMessage())) {
                    filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
                }

                lastPos = endPos + 48;
                tbb.seek(lastPos);
                filterInfo()->setCurrent((int)(((float)tbb.pos() / tbb.size()) * 100));
            }
        }
    }
    tbb.close();
}

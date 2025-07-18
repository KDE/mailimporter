/*
  filter_oe.cpp  -  Outlook Express mail import

  SPDX-FileCopyrightText: 2003 Laurence Anderson <l.d.anderson@warwick.ac.uk>
  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.Kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

// This filter was created by looking at libdbx  &liboe

#include "filteroe.h"
using namespace Qt::Literals::StringLiterals;

#include "mailimporter_debug.h"

#include <KLocalizedString>
#include <QFileDialog>

#include <QTemporaryFile>

#define OE4_SIG_1 0x36464d4a
#define OE4_SIG_2 0x00010003
#define OE5_SIG_1 0xfe12adcf
#define OE5_EMAIL_SIG_2 0x6f74fdc5
#define OE5_FOLDER_SIG_2 0x6f74fdc6
#define OE5_SIG_3 0x11d1e366
#define OE5_SIG_4 0xc0004e9a
#define MBX_MAILMAGIC 0x7F007F00

using namespace MailImporter;

FilterOE::FilterOE()
    : Filter(i18n("Import Outlook Express Emails"),
             i18n("Laurence Anderson <br>( Filter enhanced by Danny Kukawka )</p>"),
             i18n("<p><b>Outlook Express 4/5/6 import filter</b></p>"
                  "<p>You will need to locate the folder where the mailbox has been "
                  "stored by searching for .dbx or .mbx files under "
                  "<ul><li><i>C:\\Windows\\Application Data</i> in Windows 9x</li>"
                  "<li><i>Documents and Settings</i> in Windows 2000 or later</li></ul></p>"
                  "<p><b>Note:</b> Since it is possible to recreate the folder structure, the folders from "
                  "Outlook Express 5 and 6 will be stored under: \"OE-Import\" in your local folder.</p>"))
{
}

FilterOE::~FilterOE()
{
}

void FilterOE::import()
{
    // Select directory containing plain text emails
    const QString maildir = QFileDialog::getExistingDirectory(filterInfo()->parentWidget(), QString(), QDir::homePath());
    importMails(maildir);
}

void FilterOE::importMails(const QString &maildir)
{
    if (maildir.isEmpty()) { // No directory selected
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    setMailDir(maildir);

    QDir dir(mailDir());
    QStringList files = dir.entryList(QStringList(u"*.[dDmM][bB][xX]"_s), QDir::Files, QDir::Name);
    if (files.isEmpty()) {
        filterInfo()->alert(i18n("No Outlook Express mailboxes found in directory %1.", mailDir()));
        return;
    }

    totalFiles = files.count();
    currentFile = 0;
    count0x04 = 0;
    count0x84 = 0;
    parsedFolder = false;

    filterInfo()->setOverall(0);

    /** search the folderfile to recreate folder struct */

    for (QStringList::Iterator mailFile = files.begin(); mailFile != files.end(); ++mailFile) {
        if (*mailFile == QLatin1StringView("Folders.dbx")) {
            filterInfo()->addInfoLogEntry(i18n("Import folder structure..."));
            importMailBox(dir.filePath(*mailFile));
            if (!folderStructure.isEmpty()) {
                parsedFolder = true;
            }
            // remove file from QStringList::files, no longer needed
            files.erase(mailFile);
            currentIsFolderFile = false;
            break;
        }
    }

    int n = 0;
    QStringList::ConstIterator end(files.constEnd());
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        importMailBox(dir.filePath(*mailFile));
        filterInfo()->setOverall(100 * ++n / files.count());
    }

    filterInfo()->setOverall(100);
    filterInfo()->setCurrent(100);
    filterInfo()->addInfoLogEntry(i18n("Finished importing Outlook Express emails"));
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }

    qCDebug(MAILIMPORTER_LOG) << "total emails in current file:" << totalEmails;
    qCDebug(MAILIMPORTER_LOG) << "0x84 Mails:" << count0x84;
    qCDebug(MAILIMPORTER_LOG) << "0x04 Mails:" << count0x04;
}

void FilterOE::importMailBox(const QString &fileName)
{
    QFile mailfile(fileName);
    QFileInfo mailfileinfo(fileName);
    QString _nameOfFile = fileName;
    _nameOfFile.remove(mailDir());
    _nameOfFile.remove(u'/');
    filterInfo()->setFrom(mailfileinfo.fileName());

    if (!mailfile.open(QIODevice::ReadOnly)) {
        filterInfo()->addErrorLogEntry(i18n("Unable to open mailbox %1", fileName));
        return;
    }
    QDataStream mailbox(&mailfile);
    mailbox.setByteOrder(QDataStream::LittleEndian);

    // Parse magic
    quint32 sig_block1;
    quint32 sig_block2;
    mailbox >> sig_block1 >> sig_block2;
    if (sig_block1 == OE4_SIG_1 && sig_block2 == OE4_SIG_2) {
        folderName = QLatin1StringView("OE-Import/") + mailfileinfo.completeBaseName();
        filterInfo()->addInfoLogEntry(i18n("Importing OE4 Mailbox %1", u"../"_s + _nameOfFile));
        filterInfo()->setTo(folderName);
        mbxImport(mailbox);
        return;
    } else {
        quint32 sig_block3;
        quint32 sig_block4;
        mailbox >> sig_block3 >> sig_block4;
        if (sig_block1 == OE5_SIG_1 && sig_block3 == OE5_SIG_3 && sig_block4 == OE5_SIG_4) {
            if (sig_block2 == OE5_EMAIL_SIG_2) {
                folderName = QLatin1StringView("OE-Import/") + mailfileinfo.completeBaseName();
                if (parsedFolder) {
                    const QString _tmpFolder = getFolderName(_nameOfFile);
                    if (!_tmpFolder.isEmpty()) {
                        folderName = QLatin1StringView("OE-Import/") + _tmpFolder;
                    }
                }
                filterInfo()->addInfoLogEntry(i18n("Importing OE5+ Mailbox %1", u"../"_s + _nameOfFile));
                filterInfo()->setTo(folderName);
                dbxImport(mailbox);
                return;
            } else if (sig_block2 == OE5_FOLDER_SIG_2) {
                if (!parsedFolder) {
                    filterInfo()->addInfoLogEntry(i18n("Importing OE5+ Folder file %1", u"../"_s + _nameOfFile));
                    currentIsFolderFile = true;
                    dbxImport(mailbox);
                    currentIsFolderFile = false;
                }
                return;
            }
        }
    }
}

/* ------------------- MBX support ------------------- */

void FilterOE::mbxImport(QDataStream &ds)
{
    quint32 msgCount;
    quint32 lastMsgNum;
    quint32 fileSize;

    // Read the header
    ds >> msgCount >> lastMsgNum >> fileSize;
    ds.device()->seek(ds.device()->pos() + 64); // Skip 0's
    qCDebug(MAILIMPORTER_LOG) << "This mailbox has" << msgCount << " messages";
    if (msgCount == 0) {
        return; // Don't import empty mailbox
    }

    quint32 msgMagic;
    ds >> msgMagic; // Read first magic

    while (!ds.atEnd()) {
        quint32 msgNumber;
        quint32 msgSize;
        quint32 msgTextSize;
        QTemporaryFile tmp;
        tmp.open();
        QDataStream dataStream(&tmp);
        dataStream.setByteOrder(QDataStream::LittleEndian);

        // Read the messages
        ds >> msgNumber >> msgSize >> msgTextSize; // All seem to be lies...?
        do {
            ds >> msgMagic;
            if (msgMagic != MBX_MAILMAGIC) {
                dataStream << msgMagic;
            } else {
                break;
            }
        } while (!ds.atEnd());
        tmp.flush();
        if (!importMessage(folderName, tmp.fileName(), filterInfo()->removeDupMessage())) {
            filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
        }

        if (filterInfo()->shouldTerminate()) {
            return;
        }
    }
}

/* ------------------- DBX support ------------------- */

void FilterOE::dbxImport(QDataStream &ds)
{
    // Get item count  &offset of index
    quint32 itemCount;
    quint32 indexPtr;
    ds.device()->seek(0xc4);
    ds >> itemCount;
    ds.device()->seek(0xe4);
    ds >> indexPtr;
    qCDebug(MAILIMPORTER_LOG) << "Item count is" << itemCount << ", Index at" << indexPtr;

    if (itemCount == 0) {
        return; // Empty file
    }
    totalEmails = itemCount;
    currentEmail = 0;
    // Parse the indexes
    ds.device()->seek(indexPtr);
    dbxReadIndex(ds, indexPtr);
}

void FilterOE::dbxReadIndex(QDataStream &ds, int filePos)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }
    quint32 self;
    quint32 unknown;
    quint32 nextIndexPtr;
    quint32 parent;
    quint32 indexCount;
    quint8 unknown2;
    quint8 ptrCount;
    quint16 unknown3;
    int wasAt = ds.device()->pos();
    ds.device()->seek(filePos);

    qCDebug(MAILIMPORTER_LOG) << "Reading index of file" << folderName;
    ds >> self >> unknown >> nextIndexPtr >> parent >> unknown2 >> ptrCount >> unknown3 >> indexCount; // _dbx_tableindexstruct

    qCDebug(MAILIMPORTER_LOG) << "This index has" << (int)ptrCount << " data pointers";
    for (int count = 0; count < ptrCount; ++count) {
        if (filterInfo()->shouldTerminate()) {
            return;
        }
        quint32 dataIndexPtr;
        quint32 anotherIndexPtr;
        quint32 anotherIndexCount; // _dbx_indexstruct
        ds >> dataIndexPtr >> anotherIndexPtr >> anotherIndexCount;

        if (anotherIndexCount > 0) {
            qCDebug(MAILIMPORTER_LOG) << "Recursing to another table @" << anotherIndexPtr;
            dbxReadIndex(ds, anotherIndexPtr);
        }
        qCDebug(MAILIMPORTER_LOG) << "Data index @" << dataIndexPtr;
        dbxReadDataBlock(ds, dataIndexPtr);
    }

    if (indexCount > 0) { // deal with nextTablePtr
        qCDebug(MAILIMPORTER_LOG) << "Recurring to next table @" << nextIndexPtr;
        dbxReadIndex(ds, nextIndexPtr);
    }

    ds.device()->seek(wasAt); // Restore file position to same as when function called
}

void FilterOE::dbxReadDataBlock(QDataStream &ds, int filePos)
{
    quint32 curOffset;
    quint32 blockSize;
    quint16 unknown;
    quint8 count;
    quint8 unknown2;
    int wasAt = ds.device()->pos();

    QString folderEntry[4];

    ds.device()->seek(filePos);

    ds >> curOffset >> blockSize >> unknown >> count >> unknown2; // _dbx_email_headerstruct
    qCDebug(MAILIMPORTER_LOG) << "Data block has" << (int)count << " elements";

    for (int c = 0; c < count; c++) {
        if (filterInfo()->shouldTerminate()) {
            return;
        }
        quint8 type; // _dbx_email_pointerstruct
        quint32 value; // Actually 24 bit

        ds >> type >> value;
        value &= 0xffffff;
        ds.device()->seek(ds.device()->pos() - 1); // We only wanted 3 bytes

        if (!currentIsFolderFile) {
            if (type == 0x84) { // It's an email!
                qCDebug(MAILIMPORTER_LOG) << "**** Offset of emaildata (0x84)" << value << " ****";
                dbxReadEmail(ds, value);
                ++count0x84;
            } else if (type == 0x04) {
                int currentFilePos = ds.device()->pos();
                ds.device()->seek(filePos + 12 + value + (count * 4));
                quint32 newOFF;
                ds >> newOFF;
                qCDebug(MAILIMPORTER_LOG) << "**** Offset of emaildata (0x04)" << newOFF;
                ds.device()->seek(currentFilePos);
                dbxReadEmail(ds, newOFF);
                ++count0x04;
            }
        } else {
            // this is a folderfile
            if (type == 0x02) {
                // qCDebug(MAILIMPORTER_LOG) <<"**** FOLDER: descriptive name ****";
                folderEntry[0] = parseFolderOEString(ds, filePos + 12 + value + (count * 4));
            } else if (type == 0x03) {
                // qCDebug(MAILIMPORTER_LOG) <<"**** FOLDER: filename ****";
                folderEntry[1] = parseFolderOEString(ds, filePos + 12 + value + (count * 4));
            } else if (type == 0x80) {
                // qCDebug(MAILIMPORTER_LOG) <<"**** FOLDER: current ID ****";
                folderEntry[2] = QString::number(value);
            } else if (type == 0x81) {
                // qCDebug(MAILIMPORTER_LOG) <<"**** FOLDER: parent ID ****";
                folderEntry[3] = QString::number(value);
            }
        }
    }
    if (currentIsFolderFile) {
        folderStructure.append(FolderStructure(folderEntry));
    }
    ds.device()->seek(wasAt); // Restore file position to same as when function called
}

void FilterOE::dbxReadEmail(QDataStream &ds, int filePos)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }
    quint32 self;
    quint32 nextAddressOffset;
    quint32 nextAddress = 0;
    quint16 blockSize;
    quint8 intCount;
    quint8 unknown;
    QTemporaryFile tmp;
    tmp.open();
    bool _break = false;
    int wasAt = ds.device()->pos();
    ds.device()->seek(filePos);
    QDataStream tempDs(&tmp);

    do {
        ds >> self >> nextAddressOffset >> blockSize >> intCount >> unknown >> nextAddress; // _dbx_block_hdrstruct
        QByteArray blockBuffer(blockSize, '\0');
        ds.readRawData(blockBuffer.data(), blockSize);
        tempDs.writeRawData(blockBuffer.data(), blockSize);
        // to detect incomplete mails or corrupted archives. See Bug #86119
        if (ds.atEnd()) {
            _break = true;
            break;
        }
        ds.device()->seek(nextAddress);
    } while (nextAddress != 0);
    tmp.flush();

    if (!_break) {
        if (!importMessage(folderName, tmp.fileName(), filterInfo()->removeDupMessage())) {
            filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
        }

        currentEmail++;
        int currentPercentage = (int)(((float)currentEmail / totalEmails) * 100);
        filterInfo()->setCurrent(currentPercentage);
        ds.device()->seek(wasAt);
    }
}

/* ------------------- FolderFile support ------------------- */
QString FilterOE::parseFolderOEString(QDataStream &ds, int filePos)
{
    char tmp;
    QString returnString;
    int wasAt = ds.device()->pos();
    ds.device()->seek(filePos);

    // read while != 0x00
    while (!ds.device()->atEnd()) {
        ds.device()->getChar(&tmp);
        if (tmp != 0x00) {
            returnString += QLatin1Char(tmp);
        } else {
            break;
        }
    }
    ds.device()->seek(wasAt);
    return returnString;
}

/** get the foldername for a given file ID from folderMatrix */
QString FilterOE::getFolderName(const QString &filename)
{
    bool found = false;
    bool foundFilename = false;
    QString folder;
    // we must do this because folder with more than one upper letter
    // at start have maybe not a file named like the folder !!!
    QString search = filename.toLower();

    while (!found) {
        for (FolderStructureIterator it = folderStructure.begin(); it != folderStructure.end(); ++it) {
            FolderStructure tmp = *it;
            if (foundFilename == false) {
                QString _tmpFileName = tmp[1];
                _tmpFileName = _tmpFileName.toLower();
                if (_tmpFileName == search) {
                    folder.prepend(tmp[0] + QLatin1StringView("/"));
                    search = tmp[3];
                    foundFilename = true;
                }
            } else {
                QString _currentID = tmp[2];
                QString _parentID = tmp[3];
                if (_currentID == search) {
                    if (_parentID.isEmpty()) { // this is the root of the folder
                        found = true;
                        break;
                    } else {
                        folder.prepend(tmp[0] + QLatin1StringView("/"));
                        search = tmp[3];
                    }
                }
            }
        }
        // need to break the while loop maybe in some cases
        if ((foundFilename == false) && (folder.isEmpty())) {
            return folder;
        }
    }
    return folder;
}

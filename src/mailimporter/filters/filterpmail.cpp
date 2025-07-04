/*
  filterpmail.cpp  -  Pegasus-Mail import

  SPDX-FileCopyrightText: 2001 Holger Schurig <holgerschurig@gmx.de>
  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterpmail.h"
using namespace Qt::Literals::StringLiterals;

#include "mailimporter_debug.h"

#include <KLocalizedString>

#include <QFileDialog>
#include <QRegularExpression>
#include <QTemporaryFile>

using namespace MailImporter;

FilterPMail::FilterPMail()
    : Filter(i18n("Import Folders From Pegasus-Mail"),
             i18n("Holger Schurig <br>( rewritten by Danny Kukawka )"),
             i18n("<p>Select the Pegasus-Mail directory on your system (containing *.CNM, *.PMM and *.MBX files). "
                  "On many systems this is stored in C:\\pmail\\mail or C:\\pmail\\mail\\admin</p>"
                  "<p><b>Note:</b> Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"PegasusMail-Import\".</p>"))
{
}

FilterPMail::~FilterPMail()
{
}

void FilterPMail::import()
{
    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), QDir::homePath());
    importMails(maildir);
}

void FilterPMail::importMails(const QString &chosenDir)
{
    if (chosenDir.isEmpty()) {
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    setMailDir(chosenDir);

    // Count total number of files to be processed
    filterInfo()->addInfoLogEntry(i18n("Counting files..."));
    dir.setPath(mailDir());
    const QStringList files = dir.entryList(QStringList() << u"*.[cC][nN][mM]"_s << u"*.[pP][mM][mM]"_s << u"*.[mM][bB][xX]"_s, QDir::Files, QDir::Name);
    totalFiles = files.count();
    currentFile = 0;
    qCDebug(MAILIMPORTER_LOG) << "Count is" << totalFiles;

    if (!(folderParsed = parseFolderMatrix(mailDir()))) {
        filterInfo()->addErrorLogEntry(i18n("Cannot parse the folder structure; continuing import without subfolder support."));
    }

    filterInfo()->addInfoLogEntry(i18n("Importing new mail files ('.cnm')..."));
    processFiles(u"*.[cC][nN][mM]"_s, &FilterPMail::importNewMessage);
    filterInfo()->addInfoLogEntry(i18n("Importing mail folders ('.pmm')..."));
    processFiles(u"*.[pP][mM][mM]"_s, &FilterPMail::importMailFolder);
    filterInfo()->addInfoLogEntry(i18n("Importing 'UNIX' mail folders ('.mbx')..."));
    processFiles(u"*.[mM][bB][xX]"_s, &FilterPMail::importUnixMailFolder);

    filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir()));
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

/** this looks for all files with the filemask 'mask' and calls the 'workFunc' on each of them */
void FilterPMail::processFiles(const QString &mask, void (FilterPMail::*workFunc)(const QString &))
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }

    const QStringList files = dir.entryList(QStringList(mask), QDir::Files, QDir::Name);
    // qCDebug(MAILIMPORTER_LOG) <<"Mask is" << mask <<" count is" << files.count();
    QStringList::ConstIterator end = files.constEnd();
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
        // Notify current file
        QFileInfo mailfilem_filterInfoo(*mailFile);
        filterInfo()->setFrom(mailfilem_filterInfoo.fileName());

        // Clear the other fields
        filterInfo()->setTo(QString());
        filterInfo()->setCurrent(QString());
        filterInfo()->setCurrent(-1);

        // call worker function, increase progressbar
        (this->*workFunc)(dir.filePath(*mailFile));
        ++currentFile;
        filterInfo()->setOverall((int)((float)currentFile / totalFiles * 100));
        filterInfo()->setCurrent(100);
        if (filterInfo()->shouldTerminate()) {
            return;
        }
    }
}

/** this function imports one *.CNM message */
void FilterPMail::importNewMessage(const QString &file)
{
    QString destFolder(u"PegasusMail-Import/New Messages"_s);
    filterInfo()->setTo(destFolder);

    if (!importMessage(destFolder, file, filterInfo()->removeDupMessage())) {
        filterInfo()->addErrorLogEntry(i18n("Could not import %1", file));
    }
}

/** this function imports one mail folder file (*.PMM) */
void FilterPMail::importMailFolder(const QString &file)
{
    // Format of a PMM file:
    // First comes a header with 128 bytes. At the beginning is the name of
    // the folder. Then there are some unknown bytes (strings). At offset 128
    // the first message starts.
    //
    // Each message is terminated by a 0x1A byte. The next message follows
    // immediately.
    //
    // The last message is followed by a 0x1A, too.
    //
    // 000000 6d 61 69 6c 73 65 72 76 65 72 2d 70 72 6f 6a 65    mailserver-proje
    // 000010 63 74 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ct..............
    // 000020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
    // 000030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
    // 000040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
    // 000050 00 00 00 00 00 00 36 30 34 37 35 37 32 45 3a 36    ......6047572E:6
    // 000060 46 34 39 3a 46 4f 4c 30 31 33 35 35 00 00 00 00    F49:FOL01355....
    // 000070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
    // 000080 52 65 74 75 72 6e 2d 50 61 74 68 3a 20 3c 75 72    Return-Path: <ur
    // ...
    // 000cb0 2d 2d 2d 2d 2d 2d 2d 2d 2d 2b 0d 0a 1a 52 65 74    ---------+...Ret
    // 000cc0 75 72 6e 2d 50 61 74 68 3a 20 3c 62 6f 75 6e 63    urn-Path: <bounc
    // ...
    // 04dc50 46 30 33 38 44 2e 36 31 35 44 37 34 44 30 2d 2d    F038D.615D74D0--
    // 04dc60 0d 0a 1a

    struct {
        char folder[86];
        char id[42];
    } pmm_head;

    QFile f(file);
    if (!f.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", file));
    } else {
        // Get folder name
        long l = f.read((char *)&pmm_head, sizeof(pmm_head));
        QString folder(i18nc("define folder name when we will import pegasus mail", "PegasusMail-Import") + u'/');
        if (folderParsed) {
            folder.append(getFolderName(QString::fromLatin1(pmm_head.id)));
        } else {
            folder.append(QString::fromLatin1(pmm_head.folder));
        }
        filterInfo()->setTo(folder);
        filterInfo()->addInfoLogEntry(i18n("Importing %1", u"../"_s + QString::fromLatin1(pmm_head.folder)));

        QByteArray input(MAX_LINE, '\0');
        bool first_msg = true;

        while (!f.atEnd()) {
            QTemporaryFile tempfile;
            tempfile.open();
            filterInfo()->setCurrent((int)(((float)f.pos() / f.size()) * 100));

            if (!first_msg) {
                // set the filepos back to last line minus the separate char (0x1a)
                f.seek(f.pos() - l + 1);
            }

            // no problem to loose the last line in file. This only contains a separate char
            while (!f.atEnd() && (l = f.readLine(input.data(), MAX_LINE))) {
                if (filterInfo()->shouldTerminate()) {
                    return;
                }
                if (input.at(0) == 0x1a) {
                    break;
                } else {
                    tempfile.write(input.constData(), l);
                }
            }
            tempfile.flush();
            if (!importMessage(folder, tempfile.fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tempfile.fileName()));
            }

            first_msg = false;
        }
    }
    f.close();
}

/** imports a 'unix' format mail folder (*.MBX) */
void FilterPMail::importUnixMailFolder(const QString &file)
{
    struct {
        char folder[58];
        char id[31];
    } pmg_head;

    QFile f;
    QString folder(u"PegasusMail-Import/"_s);
    QString s(file);
    QString separate;
    QByteArray line(MAX_LINE, '\0');
    int n = 0;
    int l = 0;

    /** Get the folder name */
    s.replace(QRegularExpression(u"mbx$"_s), u"pmg"_s);
    s.replace(QRegularExpression(u"MBX$"_s), u"PMG"_s);
    f.setFileName(s);
    if (!f.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", s));
        return;
    } else {
        f.read((char *)&pmg_head, sizeof(pmg_head));
        f.close();

        if (folderParsed) {
            folder.append(getFolderName(QString::fromLatin1(pmg_head.id)));
        } else {
            folder.append(QString::fromLatin1(pmg_head.folder));
        }

        filterInfo()->setTo(folder);
        filterInfo()->setTo(folder);
    }

    /** Read in the mbox */
    f.setFileName(file);
    if (!f.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", s));
    } else {
        filterInfo()->addInfoLogEntry(i18n("Importing %1", u"../"_s + QString::fromLatin1(pmg_head.folder)));
        l = f.readLine(line.data(), MAX_LINE); // read the first line which is unneeded
        while (!f.atEnd()) {
            QTemporaryFile tempfile;
            tempfile.open();

            // we lost the last line, which is the first line of the new message in
            // this lopp, but this is ok, because this is the separate line with
            // "From ???@???" and we can forget them
            while (!f.atEnd() && (l = f.readLine(line.data(), MAX_LINE))
                   && ((separate = QString::fromLatin1(line.data())).left(5) != QLatin1StringView("From "))) {
                tempfile.write(line.data(), l);
                if (filterInfo()->shouldTerminate()) {
                    return;
                }
            }
            tempfile.flush();
            if (!importMessage(folder, tempfile.fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tempfile.fileName()));
            }

            n++;
            filterInfo()->setCurrent(i18n("Message %1", n));
            filterInfo()->setCurrent((int)(((float)f.pos() / f.size()) * 100));
        }
    }
    f.close();
}

/** Parse the m_filterInfoormation about folderstructure to folderMatrix */
bool FilterPMail::parseFolderMatrix(const QString &chosendir)
{
    qCDebug(MAILIMPORTER_LOG) << "Start parsing the foldermatrix.";
    filterInfo()->addInfoLogEntry(i18n("Parsing the folder structure..."));

    QFile hierarch(chosendir + QLatin1StringView("/hierarch.pm"));
    if (!hierarch.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", chosendir + QLatin1StringView("hierarch.pm")));
        return false;
    } else {
        QByteArray tmpRead;
        while (!hierarch.atEnd()) {
            tmpRead = hierarch.readLine();
            if (tmpRead.isEmpty()) {
                break;
            }
            QString tmpArray[5];
            tmpRead.remove(tmpRead.length() - 2, 2);
            QStringList tmpList = QString::fromLatin1(tmpRead).split(u',', Qt::SkipEmptyParts);
            int i = 0;
            QStringList::ConstIterator end(tmpList.constEnd());
            for (QStringList::ConstIterator it = tmpList.constBegin(); it != end; ++it, ++i) {
                QString _tmp = *it;
                if (i < 5) {
                    tmpArray[i] = _tmp.remove(u'\"');
                } else {
                    hierarch.close();
                    return false;
                }
            }
            folderMatrix.append(FolderStructure(tmpArray));
        }
    }
    hierarch.close();
    return true;
}

/** get the foldername for a given file ID from folderMatrix */
QString FilterPMail::getFolderName(const QString &ID)
{
    bool found = false;
    QString folder;
    QString search = ID;

    while (!found) {
        FolderStructureIterator end(folderMatrix.end());
        for (FolderStructureIterator it = folderMatrix.begin(); it != end; ++it) {
            FolderStructure tmp = *it;

            QString _ID = tmp[2];
            if (_ID == search) {
                QString _type = tmp[0] + tmp[1];
                if ((_type == QLatin1StringView("21"))) {
                    found = true;
                    break;
                } else {
                    folder.prepend((tmp[4] + u'/'));
                    search = tmp[3];
                }
            }
        }
    }
    return folder;
}

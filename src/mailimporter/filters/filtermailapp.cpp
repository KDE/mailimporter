/*
  filtermailapp.cpp  -  OS X Mail App import

  SPDX-FileCopyrightText: 2004 Chris Howells <howells@kde.org>
  Derived from code by:
  SPDX-FileCopyrightText: 2003 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filtermailapp.h"
#include "mailimporter_debug.h"

#include <KLocalizedString>

#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;

class MailImporter::FilterMailAppPrivate
{
public:
    QStringList mMboxFiles;
};

FilterMailApp::FilterMailApp()
    : Filter(i18n("Import From OS X Mail"),
             i18n("Chris Howells<br /><br />Filter accelerated by Danny Kukawka )"),
             i18n("<p><b>OS X Mail Import Filter</b></p>"
                  "<p>This filter imports e-mails from the Mail client in Apple Mac OS X.</p>"))
    , d(new MailImporter::FilterMailAppPrivate)
{
}

FilterMailApp::~FilterMailApp()
{
    delete d;
}

void FilterMailApp::import()
{
    const QString directory = QFileDialog::getExistingDirectory(filterInfo()->parentWidget(), QString(), QDir::homePath());
    importMails(directory);
}

void FilterMailApp::importMails(const QString &maildir)
{
    if (maildir.isEmpty()) {
        filterInfo()->alert(i18n("No files selected."));
        return;
    }
    setMailDir(maildir);
    int currentFile = 1;
    int overall_status = 0;
    bool first_msg = true;

    filterInfo()->setOverall(0);

    //   qCDebug(MAILIMPORTER_LOG) <<"starting by looking in directory" << directory;
    traverseDirectory(mailDir());

    QStringList::ConstIterator end(d->mMboxFiles.constEnd());
    for (QStringList::ConstIterator filename = d->mMboxFiles.constBegin(); filename != end; ++filename, ++currentFile) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        QFile mbox(*filename);
        if (!mbox.open(QIODevice::ReadOnly)) {
            filterInfo()->alert(i18n("Unable to open %1, skipping", *filename));
        } else {
            QFileInfo filenameInfo(*filename);
            qCDebug(MAILIMPORTER_LOG) << "importing filename" << *filename;
            QStringList name = (*filename).split(QLatin1Char('/'), Qt::SkipEmptyParts);
            QString folderName(name[name.count() - 2]);

            filterInfo()->setCurrent(0);
            filterInfo()->addInfoLogEntry(i18n("Importing emails from %1...", *filename));
            filterInfo()->setFrom(*filename);
            filterInfo()->setTo(folderName);

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

                if (!importMessage(folderName, tmp.fileName(), filterInfo()->removeDupMessage())) {
                    filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
                }

                int currentPercentage = (int)(((float)mbox.pos() / filenameInfo.size()) * 100);
                filterInfo()->setCurrent(currentPercentage);
                if (currentFile == 1) {
                    overall_status = (int)(currentPercentage * ((float)currentFile / d->mMboxFiles.count()));
                } else {
                    overall_status =
                        (int)(((currentFile - 1) * (100.0 / (float)d->mMboxFiles.count())) + (currentPercentage * (1.0 / (float)d->mMboxFiles.count())));
                }
                filterInfo()->setOverall(overall_status);
                if (filterInfo()->shouldTerminate()) {
                    break;
                }
            }

            filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", *filename));
            if (countDuplicates() > 0) {
                filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported to folder %2 in KMail",
                                                    "%1 duplicate messages not imported to folder %2 in KMail",
                                                    countDuplicates(),
                                                    folderName));
            }
            clearCountDuplicate();
            mbox.close();
        }
    }
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }
}

void FilterMailApp::traverseDirectory(const QString &dirName)
{
    QDir dir(dirName);
    dir.setFilter(QDir::Dirs | QDir::Files);

    const QFileInfoList fileinfolist = dir.entryInfoList();
    for (const QFileInfo &fi : fileinfolist) {
        const QString filename(fi.fileName());
        if (filename == QLatin1Char('.') || filename == QLatin1String("..")) {
            continue;
        }
        if (fi.isDir() && fi.isReadable()) {
            traverseDirectory(fi.filePath());
        } else {
            if (!fi.isDir() && (filename == QLatin1String("mbox"))) {
                qCDebug(MAILIMPORTER_LOG) << "adding the file" << fi.filePath();
                d->mMboxFiles.append(fi.filePath());
            }
        }
    }
}

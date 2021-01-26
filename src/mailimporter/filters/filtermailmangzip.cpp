/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filtermailmangzip.h"
#include "mailimporter_debug.h"

#include <KCompressionDevice>
#include <KLocalizedString>

#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;

FilterMailmanGzip::FilterMailmanGzip()
    : Filter(i18n("Import mailman gzip Files"),
             QStringLiteral("Laurent Montel"),
             i18n("<p><b>mailman gzip import filter</b></p>"
                  "<p>This filter will import mailman gzipped files into KMail.</p>"
                  "<p><b>Note:</b> Emails will be imported into folders named after the "
                  "file they came from, prefixed with MAILMAN-</p>"))
{
}

FilterMailmanGzip::~FilterMailmanGzip()
{
}

void FilterMailmanGzip::import()
{
    const QStringList filenames =
        QFileDialog::getOpenFileNames(filterInfo()->parentWidget(), QString(), QDir::homePath(), QStringLiteral("%1 (*.txt.gz)").arg(i18n("gzip Files")));
    importMails(filenames);
}

void FilterMailmanGzip::importMails(const QStringList &filenames)
{
    if (filenames.isEmpty()) {
        filterInfo()->alert(i18n("No files selected."));
        return;
    }
    int currentFile = 1;
    int overall_status = 0;
    bool first_msg = true;

    filterInfo()->setOverall(0);
    QStringList::ConstIterator end(filenames.constEnd());
    for (QStringList::ConstIterator filename = filenames.constBegin(); filename != end; ++filename, ++currentFile) {
        QIODevice *device = new KCompressionDevice(*filename, KCompressionDevice::GZip);
        if (!device) {
            qCDebug(MAILIMPORTER_LOG) << "Could not create KFilterDev";
            filterInfo()->alert(i18n("Unable to open archive file '%1', skipping", *filename));
            continue;
        }

        device->open(QIODevice::ReadOnly);
        QFileInfo filenameInfo(*filename);
        QString folderName(QLatin1String("MAILMAN-") + filenameInfo.completeBaseName());

        filterInfo()->setCurrent(0);
        filterInfo()->addInfoLogEntry(i18n("Importing emails from %1...", *filename));

        filterInfo()->setFrom(*filename);
        filterInfo()->setTo(folderName);

        QByteArray input(MAX_LINE, '\0');
        long l = 0;

        while (!device->atEnd()) {
            QTemporaryFile tmp;
            tmp.open();
            qint64 filepos = 0;
            /* comment by Danny:
             * Don't use QTextStream to read from mbox, better use QDataStream. QTextStream only
             * support Unicode/Latin1/Locale. So you lost information from emails with
             * charset!=Unicode/Latin1/Locale (e.g. KOI8-R) and Content-Transfer-Encoding != base64
             * (e.g. 8Bit). It also not help to convert the QTextStream to Unicode. By this you
             * get Unicode/UTF-email but KMail can't detect the correct charset.
             */
            QByteArray separate;

            /* check if the first line start with "From " (and not "From: ") and discard the line
             * in this case because some IMAP servers (e.g. Cyrus) don't accept this header line */
            if (!first_msg && ((separate = input.data()).left(5) != "From ")) {
                tmp.write(input.constData(), l);
            }

            l = device->readLine(input.data(), MAX_LINE); // read the first line, prevent "From "

            if ((separate = input.data()).left(5) != "From ") {
                separate.replace(" at ", "@");
                tmp.write(separate.constData(), separate.length());
            }

            while (!device->atEnd() && (l = device->readLine(input.data(), MAX_LINE)) && ((separate = input.data()).left(5) != "From ")) {
                tmp.write(input.constData(), l);

                // workaround to fix hang if a corrupted mbox contains some
                // binary data, for more see bug #106796
                if (device->pos() == filepos) {
                    device->seek(device->size());
                } else {
                    filepos = device->pos();
                }
            }
            tmp.flush();
            first_msg = false;

            if (tmp.size() > 0) {
                if (!importMessage(folderName, tmp.fileName(), filterInfo()->removeDupMessage())) {
                    filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
                }
            } else {
                qCWarning(MAILIMPORTER_LOG) << "Message size is 0 bytes, not importing it.";
            }

            int currentPercentage = (int)(((float)device->pos() / filenameInfo.size()) * 100);
            filterInfo()->setCurrent(currentPercentage);
            if (currentFile == 1) {
                overall_status = (int)(currentPercentage * ((float)currentFile / filenames.count()));
            } else {
                overall_status = (int)(((currentFile - 1) * (100.0 / (float)filenames.count())) + (currentPercentage * (1.0 / (float)filenames.count())));
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
        if (filterInfo()->shouldTerminate()) {
            filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
        }

        clearCountDuplicate();
        // don't forget to close the file !!!
        device->close();
        delete device;
    }
}

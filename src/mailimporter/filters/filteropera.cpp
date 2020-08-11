/*
  filteropera.cpp  -  Opera mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filteropera.h"

#include <KLocalizedString>

#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;

FilterOpera::FilterOpera()
    : Filter(i18n("Import Opera Emails"),
             QStringLiteral("Danny Kukawka"),
             i18n("<p><b>Opera email import filter</b></p>"
                  "<p>This filter will import mails from Opera mail folder. Use this filter "
                  "if you want to import all mails within a account in the Opera maildir.</p>"
                  "<p>Select the directory of the account (usually ~/.opera/mail/store/account*).</p>"
                  "<p><b>Note:</b> Emails will be imported into a folder named after the account "
                  "they came from, prefixed with OPERA-</p>"))
{
}

FilterOpera::~FilterOpera()
{
}

QString FilterOpera::isMailerFound()
{
    QDir directory(FilterOpera::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of opera application", "Opera");
    }
    return {};
}

QString FilterOpera::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1String("/.opera/");
}

void FilterOpera::importRecursive(const QDir &mailDir, const QString &accountName)
{
    // Recursive import of the MBoxes.
    const QStringList rootSubDirs = mailDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name); // Removal of . and ..
    int numSubDirs = rootSubDirs.size();
    if (numSubDirs > 0) {
        QStringList::ConstIterator end(rootSubDirs.constEnd());
        for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename) {
            QDir importDir(mailDir.path() + QLatin1Char('/') + *filename);
            const QStringList files = importDir.entryList(QStringList(QStringLiteral("*.[mM][bB][sS]")), QDir::Files, QDir::Name);
            if (files.isEmpty()) {
                importRecursive(importDir, accountName.isEmpty() ? *filename : accountName);
            } else {
                importBox(importDir, files, accountName);
            }
        }
    }
}

void FilterOpera::importBox(const QDir &importDir, const QStringList &files, const QString &accountName)
{
    int overall_status = 0;
    int totalFiles = files.count();
    int currentFile = 1;
    filterInfo()->addInfoLogEntry(i18n("Importing new mail files..."));
    QStringList::ConstIterator end(files.constEnd());
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
        filterInfo()->setCurrent(0);
        QFile operaArchiv(importDir.filePath(*mailFile));
        if (!operaArchiv.open(QIODevice::ReadOnly)) {
            filterInfo()->alert(i18n("Unable to open %1, skipping", *mailFile));
        } else {
            filterInfo()->addInfoLogEntry(i18n("Importing emails from %1...", *mailFile));
            QFileInfo filenameInfo(importDir.filePath(*mailFile));
            QString folderName;
            if (accountName.isEmpty()) {
                folderName = QString(QLatin1String("OPERA-") + importDir.dirName());
            } else {
                folderName = QString(QLatin1String("OPERA-") + accountName);
            }

            filterInfo()->setFrom(*mailFile);
            filterInfo()->setTo(folderName);

            QByteArray input(MAX_LINE, '\0');
            long l = 0;
            bool first_msg = true;

            while (!operaArchiv.atEnd()) {
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
                l = operaArchiv.readLine(input.data(), MAX_LINE); // read the first line, prevent "From "
                tmp.write(input.constData(), l);

                while (!operaArchiv.atEnd() && (l = operaArchiv.readLine(input.data(), MAX_LINE)) && ((separate = input.data()).left(5) != "From ")) {
                    /** remove in KMail unneeded Flags from Opera (for example: X-Opera-Status)*/
                    if (separate.left(8) != "X-Opera-") {
                        tmp.write(input.constData(), l);
                    }
                }
                tmp.flush();
                first_msg = false;

                if (!importMessage(folderName, tmp.fileName(), filterInfo()->removeDupMessage())) {
                    filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
                }
                int currentPercentage = (int)(((float)operaArchiv.pos() / filenameInfo.size()) * 100);
                filterInfo()->setCurrent(currentPercentage);

                if (currentFile == 1) {
                    overall_status = (int)(currentPercentage * ((float)currentFile / totalFiles));
                } else {
                    overall_status = (int)(((currentFile - 1) * (100.0 / (float)totalFiles)) + (currentPercentage * (1.0 / (float)totalFiles)));
                }

                filterInfo()->setOverall(overall_status);
                if (filterInfo()->shouldTerminate()) {
                    break;
                }
            }

            filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", *mailFile));
            if (countDuplicates() > 0) {
                filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
            }
            currentFile++;
            clearCountDuplicate();
            operaArchiv.close();
        }
        if (filterInfo()->shouldTerminate()) {
            break;
        }
    }
}

void FilterOpera::import()
{
    /** try to go to opera mailfolder in the home of the user */
    QString startdir = defaultSettingsPath() + QLatin1String("mail/store/");
    QDir d(startdir);
    if (!d.exists()) {
        startdir = QDir::homePath();
    }

    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), startdir);
    if (!maildir.isEmpty()) {
        importMails(maildir);
    }
}

void FilterOpera::importMails(const QString &maildir)
{
    setMailDir(maildir);
    if (mailDir().isEmpty()) {
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    /**
    * If the user only select homedir no import needed because
    * there should be no files and we surely import wrong files.
    */
    else if (mailDir() == QDir::homePath() || mailDir() == (QDir::homePath() + QLatin1Char('/'))) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->setOverall(0);

        QDir importDir(mailDir());
        const QStringList files = importDir.entryList(QStringList(QStringLiteral("*.[mM][bB][sS]")), QDir::Files, QDir::Name);

        // Count total number of files to be processed
        filterInfo()->addInfoLogEntry(i18n("Counting files..."));

        if (!files.isEmpty()) {
            importBox(importDir, files);
        } else {
            //opera > 9.10 stores mail in subfolder.
            importRecursive(importDir);
        }
    }
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

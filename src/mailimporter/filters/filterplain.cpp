/*
  filterplain.cpp  -  Plain mail import

  SPDX-FileCopyrightText: 2002 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterplain.h"

#include <KLocalizedString>

#include <QFileDialog>

using namespace MailImporter;

FilterPlain::FilterPlain()
    : Filter(i18n("Import Plain Text Emails"),
             i18n("Laurence Anderson <p>( Filter accelerated by Danny Kukawka )</p>"),
             i18n("<p>Select the directory containing the emails on your system. "
                  "The emails are placed in a folder with the same name as the "
                  "directory they were in, prefixed by PLAIN-</p>"
                  "<p>This filter will import all .msg, .eml and .txt emails.</p>"))
{
}

FilterPlain::~FilterPlain()
{
}

void FilterPlain::import()
{
    // Select directory containing plain text emails
    const QString mailDir = QFileDialog::getExistingDirectory(filterInfo()->parentWidget(), QString(), QDir::homePath());
    importMails(mailDir);
}

void FilterPlain::importMails(const QString &mailDir)
{
    if (mailDir.isEmpty()) { // No directory selected
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    QDir dir(mailDir);
    const QStringList files =
        dir.entryList(QStringList() << QStringLiteral("*.[eE][mM][lL]") << QStringLiteral("*.[tT][xX][tT]") << QStringLiteral("*.[mM][sS][gG]"),
                      QDir::Files,
                      QDir::Name);
    // Count total number of files to be processed
    filterInfo()->addInfoLogEntry(i18n("Counting files..."));
    int totalFiles = files.count();
    if (files.isEmpty()) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->addInfoLogEntry(i18n("Importing new mail files..."));
        QStringList::ConstIterator end(files.constEnd());
        const QString destName = QStringLiteral("PLAIN-%1").arg(dir.dirName());
        int currentFile = 0;
        for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != end; ++mailFile) {
            const QString dirRealPath = dir.filePath(*mailFile);
            filterInfo()->setFrom(dirRealPath);
            filterInfo()->setTo(destName);
            filterInfo()->setCurrent(0);
            if (!importMessage(destName, dirRealPath, filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", *mailFile));
            }

            filterInfo()->setCurrent(100);
            filterInfo()->setOverall(100 * ++currentFile / totalFiles);
            if (filterInfo()->shouldTerminate()) {
                break;
            }
        }

        filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir));
        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
        if (filterInfo()->shouldTerminate()) {
            filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
        }
    }
    clearCountDuplicate();
}

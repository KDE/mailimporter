/*
  filterlnotes.cpp  -  Lotus Notes Structured Text mail import

  SPDX-FileCopyrightText: 2005 Robert Rockers <kconfigure@rockerssoft.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterlnotes.h"

#include <KLocalizedString>

#include <QFileDialog>
#include <QTemporaryFile>

using namespace MailImporter;
class MailImporter::FilterLNotesPrivate
{
public:
    /** the working directory */
    QDir dir;
    /** which file (of d->totalFiles) is now in the work? */
    int currentFile = 1;
    /** total number of files that get imported */
    int totalFiles = 0;
};

/** Default constructor. */
FilterLNotes::FilterLNotes()
    : Filter(i18n("Import Lotus Notes Emails"),
             QStringLiteral("Robert Rockers"),
             i18n("<p><b>Lotus Notes Structured Text mail import filter</b></p>"
                  "<p>This filter will import Structure Text files from an exported Lotus Notes email "
                  "client into KMail. Use this filter if you want to import mails from Lotus or other "
                  "mailers that use Lotus Notes' Structured Text format.</p>"
                  "<p><b>Note:</b> Since it is possible to recreate the folder structure, the imported "
                  "messages will be stored in subfolders named by the files they came from under: "
                  "\"LNotes-Import\" in your local folder.</p>"))
    , d(new MailImporter::FilterLNotesPrivate)
{
}

/** Destructor. */
FilterLNotes::~FilterLNotes()
{
    delete d;
}

/**
 * Recursive import of The Bat! maildir.
 * @param info Information storage for the operation.
 */
void FilterLNotes::import()
{
    const QStringList filenames = QFileDialog::getOpenFileNames(filterInfo()->parentWidget(), QString(), QDir::homePath(), i18n("All Files (*)"));
    if (filenames.isEmpty()) {
        filterInfo()->alert(i18n("No files selected."));
        return;
    }

    d->currentFile = 1;
    d->totalFiles = filenames.count();
    filterInfo()->setOverall(0);

    // See filter_mbox.cxx for better reference.
    QStringList::ConstIterator end = filenames.constEnd();
    for (QStringList::ConstIterator filename = filenames.constBegin(); filename != end; ++filename) {
        ++d->currentFile;
        filterInfo()->addInfoLogEntry(i18n("Importing emails from %1", *filename));
        ImportLNotes(*filename);
        filterInfo()->setOverall(100 * d->currentFile / d->totalFiles);
        if (filterInfo()->shouldTerminate()) {
            break;
        }
    }
}

/**
 * Import the files within a Folder.
 * @param file The name of the file to import.
 */
void FilterLNotes::ImportLNotes(const QString &file)
{
    // See Filter_pmail.cxx for better reference

    // Format of a Lotus Notes 5 Structured Text Document w form feed
    // Each email begins with a custom Header Principal:
    // The Message ends with a 0c character

    // open the message
    QFile f(file);

    if (!f.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", file));
    } else {
        char ch = 0;
        int state = 0;
        int n = 0;
        QTemporaryFile *tempfile = nullptr;

        // Get folder name
        QFileInfo filenameInfo(file);
        QString folder(i18nc("Define folder name where we import lotus note mails", "LNotes-Import") + QLatin1Char('/') + filenameInfo.completeBaseName());
        filterInfo()->setTo(folder);

        // State machine to read the data in. The fgetc usage is probably terribly slow ...
        while (f.getChar(&ch)) {
            switch (state) {
            // new message state
            case 0:
                // open temp output file
                state = 1;
                filterInfo()->setCurrent(i18n("Message %1", n++));
                if (filterInfo()->shouldTerminate()) {
                    return;
                }

                tempfile = new QTemporaryFile;
                tempfile->setAutoRemove(false);
                tempfile->open();
                // fall through
                Q_FALLTHROUGH();
            // inside a message state
            case 1:
                if (ch == 0x0c) {
                    // close file, send it
                    tempfile->close();

                    if (!importMessage(folder, tempfile->fileName(), filterInfo()->removeDupMessage())) {
                        filterInfo()->addErrorLogEntry(i18n("Could not import %1", tempfile->fileName()));
                    }

                    tempfile->setAutoRemove(true);
                    state = 0;

                    int currentPercentage = (int)(((float)f.pos() / filenameInfo.size()) * 100);
                    filterInfo()->setCurrent(currentPercentage);
                    if (filterInfo()->shouldTerminate()) {
                        return;
                    }

                    break;
                }
                if (ch == 0x0d) {
                    break;
                }
                tempfile->putChar(ch);
                break;
            }
        }

        if (tempfile) {
            tempfile->close();
        }

        // did Folder end without 0x1a at the end?
        if (state != 0) {
            Q_ASSERT(tempfile);

            if (!importMessage(folder, tempfile->fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tempfile->fileName()));
            }
        }
        if (tempfile) {
            tempfile->setAutoRemove(true);
            delete tempfile;
        }

        f.close();
    }
}

/*
  filterpmail.h  -  Pegasus-Mail import

  SPDX-FileCopyrightText: 2001 Holger Schurig <holgerschurig@gmx.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDir>

#include "filters.h"
#include "mailimporter_utils.h"
namespace MailImporter
{
/**
 * @brief The FilterPMail class
 */
class MAILIMPORTER_EXPORT FilterPMail : public Filter
{
public:
    FilterPMail();
    ~FilterPMail() override;

    void import() override;
    void importMails(const QString &chosenDir);

protected:
    /** this looks for all files with the filemask 'mask' and calls the 'workFunc' on each of them */
    void processFiles(const QString &mask, void (FilterPMail::*workFunc)(const QString &));
    /** this function imports one *.CNM message */
    void importNewMessage(const QString &file);
    /** this function imports one mail folder file (*.PMM) */
    void importMailFolder(const QString &file);
    /** imports a 'unix' format mail folder (*.MBX) */
    void importUnixMailFolder(const QString &file);
    /** this function recreate the folder structure */
    bool parseFolderMatrix(const QString &chosenDir);
    /** this function parse the folder structure */
    QString getFolderName(const QString &ID);

private:
    /** the working directory */
    QDir dir;

    /** Folder structure here has 5 entries. */
    using FolderStructure = FolderStructureBase<5>;
    /** List with the folder matrix, which contains following strings:
      1. type (2 for root-folder, 1 for folder, 0 for mailarchiv)
      2. type (1 for root-folder, 3 for folder, 0 for mailarchiv)
      3. "ID:flag:filename" of folder/archive
      4. "ID:name" of parent folder
      5. name of folder/archive
    */
    QList<FolderStructure> folderMatrix;
    using FolderStructureIterator = QList<FolderStructure>::Iterator;

    bool folderParsed = false;

    /** which file (of totalFiles) is now in the work? */
    int currentFile = 0;
    /** total number of files that get imported */
    int totalFiles = 0;
};
}

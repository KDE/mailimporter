/*
  filter_oe.h  -  Outlook Express mail import

  SPDX-FileCopyrightText: 2003 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

#include <QList>

#include "mailimporter_utils.h"
namespace MailImporter
{
/**
 *imports outlook text messages into KMail
 *@author Laurence Anderson
 */
class MAILIMPORTER_EXPORT FilterOE : public Filter
{
public:
    FilterOE();
    ~FilterOE() override;

    void import() override;
    void importMails(const QString &maildir);

private:
    void importMailBox(const QString &fileName);
    void mbxImport(QDataStream &ds);
    void dbxImport(QDataStream &ds);
    void dbxReadIndex(QDataStream &ds, int filePos);
    void dbxReadDataBlock(QDataStream &ds, int filePos);
    void dbxReadEmail(QDataStream &ds, int filePos);

    /** helperfunctions for folder structure support */
    Q_REQUIRED_RESULT QString parseFolderOEString(QDataStream &ds, int filePos);
    Q_REQUIRED_RESULT QString getFolderName(const QString &filename);

    /** which file (of totalFiles) is now in the work? */
    int currentFile;
    /** total number of files that get imported */
    int totalFiles;
    /** total emails in current file */
    int totalEmails;
    /** which email (of totalFiles) is now in the work? */
    int currentEmail;
    /** number of imported mails with flag 0x04 */
    int count0x04;
    /** number of imported mails with flag 0x84 */
    int count0x84;

    /** true if the folderstructure is parsed */
    bool parsedFolder;
    /** true if the current parsing file is the folder file */
    bool currentIsFolderFile;

    /** Folder structure with following  4 entries:
      1. descriptive folder name
      2. filename
      3. ID of current folder
      4. ID of parent folder
    */
    using FolderStructure = FolderStructureBase<4>;
    /** matrix with information about the folder structure*/
    QList<FolderStructure> folderStructure;
    using FolderStructureIterator = QList<FolderStructure>::Iterator;

    /** name of the current folder */
    QString folderName;
    /** name of the chosen folder */
};
}


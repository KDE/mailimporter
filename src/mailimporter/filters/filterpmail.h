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
/*!
 * \class MailImporter::FilterPMail
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterPMail
 *
 * \brief The FilterPMail class.
 */
class MAILIMPORTER_EXPORT FilterPMail : public Filter
{
public:
    /*!
     * \brief Constructor for FilterPMail.
     */
    FilterPMail();
    /*!
     * \brief Destructor for FilterPMail.
     */
    ~FilterPMail() override;

    /*!
     * \brief Imports Pegasus Mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param chosenDir The directory to import from
     */
    void importMails(const QString &chosenDir);

protected:
    /*!
     * \brief Processes all files matching the given pattern.
     * \param mask The file pattern to match
     * \param workFunc The member function to call for each file
     */
    void processFiles(const QString &mask, void (FilterPMail::*workFunc)(const QString &));
    /*!
     * \brief Imports a single mail message.
     * \param file The message file to import
     */
    void importNewMessage(const QString &file);
    /*!
     * \brief Imports a mail folder file.
     * \param file The folder file to import
     */
    void importMailFolder(const QString &file);
    /*!
     * \brief Imports a Unix format mail folder.
     * \param file The Unix format folder file to import
     */
    void importUnixMailFolder(const QString &file);
    /*!
     * \brief Parses the folder matrix from the directory.
     * \param chosenDir The directory containing the folder matrix
     * \return True if the matrix was successfully parsed
     */
    bool parseFolderMatrix(const QString &chosenDir);
    /*!
     * \brief Returns the folder name for the given folder ID.
     * \param ID The folder ID
     * \return The folder name
     */
    QString getFolderName(const QString &ID);

private:
    /*! the working directory */
    QDir dir;

    /*! Folder structure here has 5 entries. */
    using FolderStructure = FolderStructureBase<5>;
    /*! List with the folder matrix, which contains following strings:
      1. type (2 for root-folder, 1 for folder, 0 for mailarchiv)
      2. type (1 for root-folder, 3 for folder, 0 for mailarchiv)
      3. "ID:flag:filename" of folder/archive
      4. "ID:name" of parent folder
      5. name of folder/archive
    */
    QList<FolderStructure> folderMatrix;
    using FolderStructureIterator = QList<FolderStructure>::Iterator;

    bool folderParsed = false;

    /*! which file (of totalFiles) is now in the work? */
    int currentFile = 0;
    /*! total number of files that get imported */
    int totalFiles = 0;
};
}

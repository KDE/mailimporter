/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <KArchive>
#include <MailImporter/MessageStatus>
#include <QString>

namespace MailImporter
{
class FilterInfo;
/*!
 * \class MailImporter::FilterImporterBase
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterImporterBase
 *
 * \brief The FilterImporterBase class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterImporterBase
{
public:
    /*!
     * \brief Constructs a FilterImporterBase.
     * \param info The FilterInfo object for logging progress
     */
    explicit FilterImporterBase(MailImporter::FilterInfo *info);
    /*!
     * \brief Destructor for FilterImporterBase.
     */
    virtual ~FilterImporterBase();
    /*!
     * \brief Imports a single message from the file system.
     * \param folderName The destination folder name
     * \param msgPath The path to the message file
     * \param duplicateCheck Whether to check for duplicate messages
     * \param status The message status
     * \return True if the message was imported successfully
     */
    [[nodiscard]] virtual bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status);
    /*!
     * \brief Imports a message from an archive file.
     * \param file The archive file
     * \param folderPath The destination folder path
     * \param nbTotal Total number of messages
     * \param fileDone Number of files processed
     * \return True if the message was imported successfully
     */
    [[nodiscard]] virtual bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone);
    /*!
     * \brief Clears import state.
     */
    virtual void clear();
    /*!
     * \brief Clears the duplicate message count.
     */
    virtual void clearCountDuplicate();
    /*!
     * \brief Returns the count of duplicate messages found.
     * \return The number of duplicates
     */
    [[nodiscard]] virtual int countDuplicates() const;
    /*!
     * \brief Returns the top-level folder path for imported messages.
     * \return The top-level folder path
     */
    [[nodiscard]] virtual QString topLevelFolder() const;

protected:
    /*!
     * \brief The FilterInfo object for logging progress.
     */
    MailImporter::FilterInfo *const mInfo;
};
}

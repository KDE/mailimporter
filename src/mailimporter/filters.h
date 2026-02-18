/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#ifndef MAX_LINE
#define MAX_LINE 4096
#endif

#include "filterinfo.h"
#include "mailimporter_export.h"

#include <MailImporter/FilterImporterBase>

#include <QDir>
#include <memory>

/*!
 * \namespace MailImporter
 * \inmodule MailImporter
 */
namespace MailImporter
{
/*!
 * \class MailImporter::Filter
 * \inmodule MailImporter
 * \inheaderfile MailImporter/Filter
 *
 * \brief The Filter class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT Filter
{
public:
    /*!
     * \brief Constructs a Filter with name, author, and optional info.
     * \param name The filter name
     * \param author The filter author
     * \param info Optional information about the filter
     */
    explicit Filter(const QString &name, const QString &author, const QString &info = QString());
    /*!
     * \brief Destructor for Filter.
     */
    virtual ~Filter();
    /*!
     * \brief Pure virtual method to perform the mail import.
     */
    virtual void import() = 0;

    /*!
     * \brief Returns the author of the filter.
     * \return The author name
     */
    [[nodiscard]] QString author() const;
    /*!
     * \brief Returns the name of the filter.
     * \return The filter name
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief Returns information about the filter.
     * \return The filter information
     */
    [[nodiscard]] QString info() const;

    /*!
     * \brief Sets the author of the filter.
     * \param author The author name
     */
    void setAuthor(const QString &);
    /*!
     * \brief Sets the name of the filter.
     * \param name The filter name
     */
    void setName(const QString &);
    /*!
     * \brief Sets the information about the filter.
     * \param info The filter information
     */
    void setInfo(const QString &);

    /*!
     * \brief Clears all filter data.
     */
    void clear();
    /*!
     * \brief Sets the FilterInfo object used by this filter.
     * \param info The FilterInfo object
     */
    void setFilterInfo(MailImporter::FilterInfo *info);

    /*!
     * \brief Returns the FilterInfo object associated with this filter.
     * \return The FilterInfo object
     */
    MailImporter::FilterInfo *filterInfo() const;

    /*!
     * \brief Sets the FilterImporterBase object used by this filter.
     * \param importer The FilterImporterBase object
     */
    void setFilterImporter(MailImporter::FilterImporterBase *importer);
    /*!
     * \brief Returns the FilterImporterBase object associated with this filter.
     * \return The FilterImporterBase object
     */
    MailImporter::FilterImporterBase *filterImporter() const;

    /*!
     * \brief Clears the duplicate message count.
     */
    void clearCountDuplicate();
    /*!
     * \brief Returns the count of duplicate messages found.
     * \return The number of duplicates
     */
    [[nodiscard]] int countDuplicates() const;

    /*!
     * \brief Sets the mail directory to be imported.
     * \param mailDir The path to the mail directory
     */
    void setMailDir(const QString &mailDir);
    /*!
     * \brief Returns the mail directory being imported.
     * \return The mail directory path
     */
    [[nodiscard]] QString mailDir() const;

protected:
    /*!
     * \brief Counts the number of files in a directory.
     * \param dir The directory to count files in
     * \param searchHiddenDirectory Whether to search hidden directories
     * \return The number of files found
     */
    static int countDirectory(const QDir &dir, bool searchHiddenDirectory);
    /*!
     * \brief Imports a single message from the specified path.
     * \param folderName The destination folder name
     * \param msgPath The path to the message file
     * \param duplicateCheck Whether to check for duplicate messages
     * \param status The message status
     * \return True if the message was imported successfully
     */
    [[nodiscard]] bool
    importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MessageStatus &status = MailImporter::MessageStatus());

private:
    class FilterPrivate;
    std::unique_ptr<FilterPrivate> const d;
};
}

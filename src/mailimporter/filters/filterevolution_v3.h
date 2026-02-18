/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
class FilterEvolution_v3Private;
/*!
 * \class MailImporter::FilterEvolution_v3
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterEvolution_v3
 *
 * \brief The FilterEvolution_v3 class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterEvolution_v3 : public Filter
{
public:
    /*!
     * \brief Constructor for FilterEvolution_v3.
     */
    FilterEvolution_v3();
    /*!
     * \brief Destructor for FilterEvolution_v3.
     */
    ~FilterEvolution_v3() override;

    /*!
     * \brief Imports Evolution v3.x mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);
    /*!
     * \brief Returns the default settings path for Evolution v3.x.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Evolution v3.x mail client is found on the system.
     * \return A status message indicating if Evolution v3.x was found
     */
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    std::unique_ptr<FilterEvolution_v3Private> const d;
};
}

/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
#include <memory>
namespace MailImporter
{
class FilterBalsaPrivate;

/*!
 * \class MailImporter::FilterBalsa
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterBalsa
 *
 * \brief The FilterBalsa class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterBalsa : public Filter
{
public:
    /*!
     * \brief Constructor for FilterBalsa.
     */
    FilterBalsa();
    /*!
     * \brief Destructor for FilterBalsa.
     */
    ~FilterBalsa() override;

    /*!
     * \brief Imports Balsa mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);
    /*!
     * \brief Returns the default settings path for Balsa.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Balsa mail client is found on the system.
     * \return A status message indicating if Balsa was found
     */
    [[nodiscard]] static QString isMailerFound();
    /*!
     * \brief Returns the local mail directory path.
     * \return The local mail directory path
     */
    [[nodiscard]] QString localMailDirPath();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    std::unique_ptr<FilterBalsaPrivate> const d;
};
}

/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filtersylpheed.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterClawsMail
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterClawsMail
 *
 * \brief Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterClawsMail : public FilterSylpheed
{
public:
    /*!
     * \brief Constructor for FilterClawsMail.
     */
    FilterClawsMail();
    /*!
     * \brief Destructor for FilterClawsMail.
     */
    ~FilterClawsMail() override;

    /*!
     * \brief Returns the default settings path for Claws Mail.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Claws Mail client is found on the system.
     * \return A status message indicating if Claws Mail was found
     */
    [[nodiscard]] static QString isMailerFound();

    /* return local mail dir from folderlist.xml*/
    /*!
     * \brief Returns the local mail directory path.
     * \return The local mail directory path
     */
    [[nodiscard]] QString localMailDirPath() override;
    /*!
     * \brief Checks if a file should be excluded from import.
     * \param file The file path to check
     * \return True if the file should be excluded
     */
    [[nodiscard]] bool excludeFile(const QString &file) override;
    /*!
     * \brief Returns the default installation folder for Claws Mail.
     * \return The default installation folder
     */
    [[nodiscard]] QString defaultInstallFolder() const override;
    /*!
     * \brief Returns the mark file path.
     * \return The mark file path
     */
    [[nodiscard]] QString markFile() const override;
};
}

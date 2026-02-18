/*
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterEvolution
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterEvolution
 *
 * \brief Imports Evolution mboxes recursively, keeping the folder structure.
 * \author Simon MARTIN
 */
class MAILIMPORTER_EXPORT FilterEvolution : public Filter
{
public:
    /*!
     * \brief Constructor for FilterEvolution.
     */
    FilterEvolution();
    /*!
     * \brief Destructor for FilterEvolution.
     */
    ~FilterEvolution() override;

    /*!
     * \brief Imports Evolution mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);
    /*!
     * \brief Returns the default settings path for Evolution.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Evolution mail client is found on the system.
     * \return A status message indicating if Evolution was found
     */
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &, const QString &, const QString &);
    MAILIMPORTER_NO_EXPORT void importMBox(const QString &, const QString &, const QString &);
};
}

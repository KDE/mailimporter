/*
  filterevolution_v2.h  -  Evolution 2.0.x mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  Inspired and partly copied from filterevolution
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/*!
 * \class MailImporter::FilterEvolution_v2
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterEvolution_v2
 *
 * \brief Imports Evolution v2.x mail folder recursively, keeping the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterEvolution_v2 : public Filter
{
public:
    /*!
     * \brief Constructor for FilterEvolution_v2.
     */
    FilterEvolution_v2();
    /*!
     * \brief Destructor for FilterEvolution_v2.
     */
    ~FilterEvolution_v2() override;

    /*!
     * \brief Imports Evolution v2.x mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);
    /*!
     * \brief Returns the default settings path for Evolution v2.x.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Evolution v2.x mail client is found on the system.
     * \return A status message indicating if Evolution v2.x was found
     */
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &, const QString &, const QString &);
    MAILIMPORTER_NO_EXPORT void importMBox(const QString &, const QString &, const QString &);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool excludeFiles(const QString &file);
};
}

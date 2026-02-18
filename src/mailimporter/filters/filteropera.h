/*
  filteropera.h  -  Opera mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
#include <QDir>
namespace MailImporter
{
/*!
 * \class MailImporter::FilterOpera
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterOpera
 *
 * \brief imports opera account-archives into KMail.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterOpera : public Filter
{
public:
    /*!
     * \brief Constructor for FilterOpera.
     */
    FilterOpera();
    /*!
     * \brief Destructor for FilterOpera.
     */
    ~FilterOpera() override;

    /*!
     * \brief Imports Opera mail account folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);
    /*!
     * \brief Returns the default settings path for Opera.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Opera mail client is found on the system.
     * \return A status message indicating if Opera was found
     */
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importBox(const QDir &importDir, const QStringList &, const QString &accountName = QString());
    MAILIMPORTER_NO_EXPORT void importRecursive(const QDir &maildir, const QString &accountName = QString());
};
}

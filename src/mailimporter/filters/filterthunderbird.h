/*
  filterthunderbird.h  -  Thunderbird mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/*!
 * \class MailImporter::FilterThunderbird
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterThunderbird
 *
 * \brief Imports Thunderbird mail folder recursively, keeping the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterThunderbird : public Filter
{
public:
    /*!
     * \brief Constructor for FilterThunderbird.
     */
    FilterThunderbird();
    /*!
     * \brief Destructor for FilterThunderbird.
     */
    ~FilterThunderbird() override;

    /*!
     * \brief Imports Thunderbird mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);

    /*!
     * \brief Returns the default settings path for Thunderbird.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Returns the default profile for Thunderbird.
     * \param defaultSettingPath The default settings path
     * \param parent The parent widget
     * \return The default profile path
     */
    [[nodiscard]] static QString defaultProfile(const QString &defaultSettingPath, QWidget *parent = nullptr);
    /*!
     * \brief Returns a list of all available Thunderbird profiles.
     * \param currentProfile The current profile (output parameter)
     * \param defaultSettingPath The default settings path
     * \return A map of profile names to paths
     */
    [[nodiscard]] static QMap<QString, QString> listProfile(QString &currentProfile, const QString &defaultSettingPath);

    /*!
     * \brief Checks if Thunderbird mail client is found on the system.
     * \return A status message indicating if Thunderbird was found
     */
    [[nodiscard]] static QString isMailerFound();

protected:
    /*!
     * \brief Returns the default installation folder for Thunderbird.
     * \return The default installation folder
     */
    [[nodiscard]] virtual QString defaultInstallFolder() const;
    /*!
     * \brief Returns the settings folder path.
     * \return The settings folder path
     */
    [[nodiscard]] virtual QString settingsPath();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &, const QString &, const QString &);
    MAILIMPORTER_NO_EXPORT void importMBox(const QString &, const QString &, const QString &);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool excludeFiles(const QString &file);
};
}

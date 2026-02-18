/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filterthunderbird.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterIcedove
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterIcedove
 *
 * \brief The FilterIcedove class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterIcedove : public FilterThunderbird
{
public:
    /*!
     * \brief Constructor for FilterIcedove.
     */
    FilterIcedove();
    /*!
     * \brief Destructor for FilterIcedove.
     */
    ~FilterIcedove() override;

    /*!
     * \brief Returns the default settings path for Icedove.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Icedove mail client is found on the system.
     * \return A status message indicating if Icedove was found
     */
    [[nodiscard]] static QString isMailerFound();

protected:
    /*!
     * \brief Returns the default installation folder for Icedove.
     * \return The default installation folder
     */
    [[nodiscard]] QString defaultInstallFolder() const override;
    /*!
     * \brief Returns the settings folder path.
     * \return The settings folder path
     */
    [[nodiscard]] QString settingsPath() override;
};
}

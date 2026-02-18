/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filterthunderbird.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterSeaMonkey
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterSeaMonkey
 *
 * \brief The FilterSeaMonkey class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterSeaMonkey : public FilterThunderbird
{
public:
    /*!
     * \brief Constructor for FilterSeaMonkey.
     */
    FilterSeaMonkey();
    /*!
     * \brief Destructor for FilterSeaMonkey.
     */
    ~FilterSeaMonkey() override;

    /*!
     * \brief Returns the default settings path for SeaMonkey.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();

protected:
    /*!
     * \brief Returns the default installation folder for SeaMonkey.
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

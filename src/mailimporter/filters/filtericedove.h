/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filterthunderbird.h"
namespace MailImporter
{
/**
 * @brief The FilterIcedove class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterIcedove : public FilterThunderbird
{
public:
    FilterIcedove();
    ~FilterIcedove() override;

    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString isMailerFound();

protected:
    [[nodiscard]] QString defaultInstallFolder() const override;
    [[nodiscard]] QString settingsPath() override;
};
}

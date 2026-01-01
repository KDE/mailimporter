/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filterthunderbird.h"
namespace MailImporter
{
/**
 * @brief The FilterSeaMonkey class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterSeaMonkey : public FilterThunderbird
{
public:
    FilterSeaMonkey();
    ~FilterSeaMonkey() override;

    [[nodiscard]] static QString defaultSettingsPath();

protected:
    [[nodiscard]] QString defaultInstallFolder() const override;
    [[nodiscard]] QString settingsPath() override;
};
}

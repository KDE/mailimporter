/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT static QString defaultSettingsPath();

protected:
    Q_REQUIRED_RESULT QString defaultInstallFolder() const override;
    Q_REQUIRED_RESULT QString settingsPath() override;
};
}

/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <QString>

namespace MailImporter
{
namespace OtherMailerUtil
{
[[nodiscard]] MAILIMPORTER_EXPORT QString trojitaDefaultPath();
[[nodiscard]] MAILIMPORTER_EXPORT QString gearyDefaultPath();
[[nodiscard]] MAILIMPORTER_EXPORT QStringList isMailerFound();
[[nodiscard]] MAILIMPORTER_EXPORT QString nylasMailDefaultPath();
}
}

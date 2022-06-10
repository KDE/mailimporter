/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <QString>

namespace MailImporter
{
namespace OtherMailerUtil
{
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString trojitaDefaultPath();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString gearyDefaultPath();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QStringList isMailerFound();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString nylasMailDefaultPath();
}
}

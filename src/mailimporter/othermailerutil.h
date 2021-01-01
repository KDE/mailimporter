/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef OTHERMAILERUTIL_H
#define OTHERMAILERUTIL_H

#include <QString>
#include "mailimporter_export.h"

namespace MailImporter {
namespace OtherMailerUtil {
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString trojitaDefaultPath();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString gearyDefaultPath();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QStringList isMailerFound();
Q_REQUIRED_RESULT MAILIMPORTER_EXPORT QString nylasMailDefaultPath();
}
}

#endif // OTHERMAILERUTIL_H

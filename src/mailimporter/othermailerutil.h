/*
  Copyright (c) 2013-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

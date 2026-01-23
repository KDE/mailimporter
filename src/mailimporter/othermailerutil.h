/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <QString>

namespace MailImporter
{
/*!
 * \namespace MailImporter::OtherMailerUtil
 * \inmodule MailImporter
 * \inheaderfile MailImporter/OtherMailerUtil
 *
 * \brief Utility functions for detecting and accessing other mail clients.
 */
namespace OtherMailerUtil
{
/*!
 * \brief Returns the default path for Trojita mail client configuration.
 * \return The default Trojita path.
 */
[[nodiscard]] MAILIMPORTER_EXPORT QString trojitaDefaultPath();
/*!
 * \brief Returns the default path for Geary mail client data.
 * \return The default Geary path.
 */
[[nodiscard]] MAILIMPORTER_EXPORT QString gearyDefaultPath();
/*!
 * \brief Checks for installed mail clients and returns their names.
 * \return A list of found mail client names.
 */
[[nodiscard]] MAILIMPORTER_EXPORT QStringList isMailerFound();
/*!
 * \brief Returns the default path for Nylas Mail client data.
 * \return The default Nylas Mail path.
 */
[[nodiscard]] MAILIMPORTER_EXPORT QString nylasMailDefaultPath();
}
}

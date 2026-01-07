/*
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
/*!
 * Imports Evolution mboxes recursively, keeping the folder structure.
 * \author Simon MARTIN
 */
class MAILIMPORTER_EXPORT FilterEvolution : public Filter
{
public:
    /*!
     */
    FilterEvolution();
    /*!
     */
    ~FilterEvolution() override;

    /*!
     */
    void import() override;
    /*!
     */
    void importMails(const QString &maildir);
    /*!
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     */
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &, const QString &, const QString &);
    MAILIMPORTER_NO_EXPORT void importMBox(const QString &, const QString &, const QString &);
};
}

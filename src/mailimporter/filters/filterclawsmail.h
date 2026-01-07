/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filtersylpheed.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterClawsMail
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterClawsMail
 *
 * \brief Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterClawsMail : public FilterSylpheed
{
public:
    /*!
     */
    FilterClawsMail();
    /*!
     */
    ~FilterClawsMail() override;

    /*!
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     */
    [[nodiscard]] static QString isMailerFound();

    /* return local mail dir from folderlist.xml*/
    /*!
     */
    [[nodiscard]] QString localMailDirPath() override;
    /*!
     */
    [[nodiscard]] bool excludeFile(const QString &file) override;
    /*!
     */
    [[nodiscard]] QString defaultInstallFolder() const override;
    /*!
     */
    [[nodiscard]] QString markFile() const override;
};
}

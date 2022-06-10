/*
  SPDX-FileCopyrightText: 2012-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>

#include "filtersylpheed.h"
namespace MailImporter
{
/**
 * Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * @author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterClawsMail : public FilterSylpheed
{
public:
    FilterClawsMail();
    ~FilterClawsMail() override;

    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();

    /* return local mail dir from folderlist.xml*/
    Q_REQUIRED_RESULT QString localMailDirPath() override;
    Q_REQUIRED_RESULT bool excludeFile(const QString &file) override;
    Q_REQUIRED_RESULT QString defaultInstallFolder() const override;
    Q_REQUIRED_RESULT QString markFile() const override;
};
}

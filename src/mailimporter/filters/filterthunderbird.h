/*
  filterthunderbird.h  -  Thunderbird mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/**
 * Imports Thunderbird mail folder recursively, keeping the folder structure.
 * @author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterThunderbird : public Filter
{
public:
    FilterThunderbird();
    ~FilterThunderbird() override;

    void import() override;
    void importMails(const QString &maildir);

    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString defaultProfile(const QString &defaultSettingPath, QWidget *parent = nullptr);
    Q_REQUIRED_RESULT static QMap<QString, QString> listProfile(QString &currentProfile, const QString &defaultSettingPath);

    Q_REQUIRED_RESULT static QString isMailerFound();

protected:
    Q_REQUIRED_RESULT virtual QString defaultInstallFolder() const;
    Q_REQUIRED_RESULT virtual QString settingsPath();

private:
    void importDirContents(const QString &, const QString &, const QString &);
    void importMBox(const QString &, const QString &, const QString &);
    Q_REQUIRED_RESULT bool excludeFiles(const QString &file);
};
}


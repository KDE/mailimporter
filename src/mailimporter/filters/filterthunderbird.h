/*
  filterthunderbird.h  -  Thunderbird mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString defaultProfile(const QString &defaultSettingPath, QWidget *parent = nullptr);
    [[nodiscard]] static QMap<QString, QString> listProfile(QString &currentProfile, const QString &defaultSettingPath);

    [[nodiscard]] static QString isMailerFound();

protected:
    [[nodiscard]] virtual QString defaultInstallFolder() const;
    [[nodiscard]] virtual QString settingsPath();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &, const QString &, const QString &);
    MAILIMPORTER_NO_EXPORT void importMBox(const QString &, const QString &, const QString &);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool excludeFiles(const QString &file);
};
}

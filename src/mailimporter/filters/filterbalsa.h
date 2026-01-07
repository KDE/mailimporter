/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
#include <memory>
namespace MailImporter
{
class FilterBalsaPrivate;
/**
 * @brief The FilterBalsa class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterBalsa : public Filter
{
public:
    FilterBalsa();
    ~FilterBalsa() override;

    void import() override;
    void importMails(const QString &maildir);
    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString isMailerFound();
    QString localMailDirPath();

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    std::unique_ptr<FilterBalsaPrivate> const d;
};
}

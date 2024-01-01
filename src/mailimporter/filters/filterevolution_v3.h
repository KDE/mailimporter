/*
  SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
class FilterEvolution_v3Private;
/**
 * @brief The FilterEvolution_v3 class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterEvolution_v3 : public Filter
{
public:
    FilterEvolution_v3();
    ~FilterEvolution_v3() override;

    void import() override;
    void importMails(const QString &maildir);
    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString isMailerFound();

private:
    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    std::unique_ptr<FilterEvolution_v3Private> const d;
};
}

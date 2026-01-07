/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <KArchive>
#include <MailImporter/MessageStatus>
#include <QString>

namespace MailImporter
{
class FilterInfo;
/**
 * @brief The FilterImporterBase class
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterImporterBase
{
public:
    explicit FilterImporterBase(MailImporter::FilterInfo *info);
    virtual ~FilterImporterBase();
    [[nodiscard]] virtual bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status);
    [[nodiscard]] virtual bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone);
    virtual void clear();
    virtual void clearCountDuplicate();
    [[nodiscard]] virtual int countDuplicates() const;
    [[nodiscard]] virtual QString topLevelFolder() const;

protected:
    MailImporter::FilterInfo *const mInfo;
};
}

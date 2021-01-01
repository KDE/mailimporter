/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FILTERIMPORTERBASE_H
#define FILTERIMPORTERBASE_H

#include "mailimporter_export.h"
#include <MailImporter/MessageStatus>
#include <QString>
#include <KArchive>

namespace MailImporter {
class FilterInfo;
/**
 * @brief The FilterImporterBase class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterImporterBase
{
public:
    explicit FilterImporterBase(MailImporter::FilterInfo *info);
    virtual ~FilterImporterBase();
    Q_REQUIRED_RESULT virtual bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status);
    Q_REQUIRED_RESULT virtual bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone);
    virtual void clear();
    virtual void clearCountDuplicate();
    Q_REQUIRED_RESULT virtual int countDuplicates() const;
    Q_REQUIRED_RESULT virtual QString topLevelFolder() const;
protected:
    MailImporter::FilterInfo *const mInfo;
};
}
#endif // FILTERIMPORTERBASE_H

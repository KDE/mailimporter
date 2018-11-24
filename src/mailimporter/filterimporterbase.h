/*
  Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef FILTERIMPORTERBASE_H
#define FILTERIMPORTERBASE_H

#include "mailimporter_export.h"
#include <MailImporter/MessageStatus>
#include <QString>
#include <KArchive>

namespace MailImporter {
class FilterInfo;
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
    MailImporter::FilterInfo *mInfo = nullptr;
};
}
#endif // FILTERIMPORTERBASE_H

/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef FILTERIMPORTERTEST_H
#define FILTERIMPORTERTEST_H

#include <MailImporter/FilterImporterBase>
#include <QObject>
#include <QVector>
struct FilterImporterData {
    QString folderName;
    QString msgPath;
    MailImporter::MessageStatus status;
};

class FilterImporterTest : public MailImporter::FilterImporterBase
{
public:
    explicit FilterImporterTest(MailImporter::FilterInfo *info);
    ~FilterImporterTest() = default;

    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status) Q_DECL_OVERRIDE;
    void clear() Q_DECL_OVERRIDE;
    void clearCountDuplicate() Q_DECL_OVERRIDE;
    int countDuplicates() const Q_DECL_OVERRIDE;
    QString topLevelFolder() const Q_DECL_OVERRIDE;

    bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone) Q_DECL_OVERRIDE;
    QVector<FilterImporterData> filterImporterDataList() const;

private:
    QVector<FilterImporterData> mFilterImporterDataList;
};

#endif // FILTERIMPORTERTEST_H

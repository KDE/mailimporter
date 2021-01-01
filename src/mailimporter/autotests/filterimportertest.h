/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERIMPORTERTEST_H
#define FILTERIMPORTERTEST_H

#include <MailImporter/FilterImporterBase>
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

    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status) override;
    void clear() override;
    void clearCountDuplicate() override;
    int countDuplicates() const override;
    QString topLevelFolder() const override;

    bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone) override;
    QVector<FilterImporterData> filterImporterDataList() const;

private:
    QVector<FilterImporterData> mFilterImporterDataList;
};

#endif // FILTERIMPORTERTEST_H

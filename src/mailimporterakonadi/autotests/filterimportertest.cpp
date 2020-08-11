/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filterimportertest.h"
#include <QDebug>

FilterImporterTest::FilterImporterTest(MailImporter::FilterInfo *info)
    : MailImporter::FilterImporterBase(info)
{
}

bool FilterImporterTest::importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status)
{
    Q_UNUSED(status)
    qDebug() << "FilterImporterTest::importMessage folderName " << folderName << " msgPath " << msgPath << " duplicateCheck " << duplicateCheck;
    return false;
}

void FilterImporterTest::clear()
{
}

void FilterImporterTest::clearCountDuplicate()
{
}

int FilterImporterTest::countDuplicates() const
{
    return 0;
}

QString FilterImporterTest::topLevelFolder() const
{
    return {};
}

bool FilterImporterTest::importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone)
{
    Q_UNUSED(file);
    Q_UNUSED(folderPath);
    Q_UNUSED(nbTotal);
    Q_UNUSED(fileDone);

    return false;
}

QVector<FilterImporterData> FilterImporterTest::filterImporterDataList() const
{
    return mFilterImporterDataList;
}

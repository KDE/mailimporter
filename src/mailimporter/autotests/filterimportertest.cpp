/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterimportertest.h"
#include <QDebug>

FilterImporterTest::FilterImporterTest(MailImporter::FilterInfo *info)
    : MailImporter::FilterImporterBase(info)
{
}

bool FilterImporterTest::importMessage([[maybe_unused]] const QString &folderName,
                                       [[maybe_unused]] const QString &msgPath,
                                       [[maybe_unused]] bool duplicateCheck,
                                       [[maybe_unused]] const MailImporter::MessageStatus &status)
{
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

bool FilterImporterTest::importMessage([[maybe_unused]] const KArchiveFile *file,
                                       [[maybe_unused]] const QString &folderPath,
                                       [[maybe_unused]] int &nbTotal,
                                       [[maybe_unused]] int &fileDone)
{
    return false;
}

QList<FilterImporterData> FilterImporterTest::filterImporterDataList() const
{
    return mFilterImporterDataList;
}

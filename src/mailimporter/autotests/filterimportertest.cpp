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


#include "filterimportertest.h"
#include <QDebug>

FilterImporterTest::FilterImporterTest(MailImporter::FilterInfo *info)
    : MailImporter::FilterImporterBase(info)
{

}

bool FilterImporterTest::importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status)
{
    qDebug() << "FilterImporterTest::importMessage folderName " << folderName << " msgPath " << msgPath;
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

    return false;
}

QVector<FilterImporterData> FilterImporterTest::filterImporterDataList() const
{
    return mFilterImporterDataList;
}

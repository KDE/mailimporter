/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "filterthebattest.h"
#include <MailImporter/FilterTheBat>
#include "filterimportertest.h"
#include <qtest.h>

FilterTheBatTest::FilterTheBatTest(QObject *parent)
    : QObject(parent)
{

}

FilterTheBatTest::~FilterTheBatTest()
{

}

void FilterTheBatTest::shouldImportData()
{

}

void FilterTheBatTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterTheBatTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterTheBatTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

QTEST_MAIN(FilterTheBatTest)

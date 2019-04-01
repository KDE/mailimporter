/*
  Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "filtermboxtest.h"
#include <MailImporter/FilterMBox>
#include "filterimportertest.h"
#include <QTest>

FilterMBoxTest::FilterMBoxTest(QObject *parent)
    : QObject(parent)
{
}

FilterMBoxTest::~FilterMBoxTest()
{
}

void FilterMBoxTest::shouldImportData()
{
}

void FilterMBoxTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterMBox filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringList());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterMBoxTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterMBox filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringList() << QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

QTEST_MAIN(FilterMBoxTest)

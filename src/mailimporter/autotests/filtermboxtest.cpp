/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
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
    MailImporter::FilterInfo info;
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterMBoxTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterMBox filter;
    MailImporter::FilterInfo info;
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList() << QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMBoxTest)

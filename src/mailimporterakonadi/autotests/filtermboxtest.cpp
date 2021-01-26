/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filtermboxtest.h"
#include "filterimportertest.h"
#include <MailImporter/FilterMBox>
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
    auto *importerTest = new FilterImporterTest(&info);
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
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList() << QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMBoxTest)

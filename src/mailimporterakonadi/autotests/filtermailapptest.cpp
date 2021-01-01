/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filtermailapptest.h"
#include <MailImporter/FilterMailApp>
#include "filterimportertest.h"
#include <QTest>

FilterMailAppTest::FilterMailAppTest(QObject *parent)
    : QObject(parent)
{
}

FilterMailAppTest::~FilterMailAppTest()
{
}

void FilterMailAppTest::shouldImportData()
{
}

void FilterMailAppTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterMailApp filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterMailAppTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterMailApp filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMailAppTest)

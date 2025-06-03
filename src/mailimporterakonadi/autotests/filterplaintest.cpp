/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterplaintest.h"
#include "filterimportertest.h"
#include <MailImporter/FilterPlain>
#include <QTest>

FilterPlainTest::FilterPlainTest(QObject *parent)
    : QObject(parent)
{
}

FilterPlainTest::~FilterPlainTest()
{
}

void FilterPlainTest::shouldImportData()
{
}

void FilterPlainTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterPlain filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterPlainTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterPlain filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterPlainTest)

#include "moc_filterplaintest.cpp"

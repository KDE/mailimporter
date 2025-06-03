/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterbalsamailtest.h"
#include "filterimportertest.h"
#include <MailImporter/FilterBalsa>
#include <QTest>

FilterBalsaMailTest::FilterBalsaMailTest(QObject *parent)
    : QObject(parent)
{
}

FilterBalsaMailTest::~FilterBalsaMailTest()
{
}

void FilterBalsaMailTest::shouldImportData()
{
}

void FilterBalsaMailTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterBalsa filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterBalsaMailTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterBalsa filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterBalsaMailTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterBalsa filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterBalsaMailTest)

#include "moc_filterbalsamailtest.cpp"

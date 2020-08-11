/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filterbalsamailtest.h"
#include <MailImporter/FilterBalsa>
#include "filterimportertest.h"
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
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
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
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
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
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterBalsaMailTest)

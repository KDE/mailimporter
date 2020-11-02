/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filtersylpheedtest.h"
#include "filterimportertestutil.h"
#include <MailImporter/FilterSylpheed>
#include "filterimportertest.h"
#include <QTest>

FilterSylpheedTest::FilterSylpheedTest(QObject *parent)
    : QObject(parent)
{
}

FilterSylpheedTest::~FilterSylpheedTest()
{
}

void FilterSylpheedTest::shouldImportData()
{
}

void FilterSylpheedTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterSylpheed filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterSylpheedTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterSylpheed filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterSylpheedTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterSylpheed filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterSylpheedTest)

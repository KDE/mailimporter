/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filtersylpheedtest.h"
using namespace Qt::Literals::StringLiterals;

#include "filterimportertest.h"
#include "filterimportertestutil.h"
#include <MailImporter/FilterSylpheed>
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
    auto importerTest = new FilterImporterTest(&info);
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
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(u"/foo/kde/bla/toto/"_s);
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterSylpheedTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterSylpheed filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterSylpheedTest)

#include "moc_filtersylpheedtest.cpp"

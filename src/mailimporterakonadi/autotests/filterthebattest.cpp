/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filterthebattest.h"
#include <MailImporter/FilterTheBat>
#include "filterimportertest.h"
#include <QTest>

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
    MailImporter::FilterInfo info;
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterTheBatTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo info;
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterTheBatTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo info;
    FilterImporterTest *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterTheBatTest)

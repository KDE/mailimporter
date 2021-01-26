/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filterclawsmailtest.h"
#include "filterimportertest.h"
#include <MailImporter/FilterClawsMail>
#include <QTest>

FilterClawsMailTest::FilterClawsMailTest(QObject *parent)
    : QObject(parent)
{
}

FilterClawsMailTest::~FilterClawsMailTest()
{
}

void FilterClawsMailTest::shouldImportData()
{
}

void FilterClawsMailTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterClawsMail filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterClawsMailTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterClawsMail filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterClawsMailTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterClawsMail filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterClawsMailTest)

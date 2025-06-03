/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filtermailapptest.h"
#include "filterimportertest.h"
#include <MailImporter/FilterMailApp>
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
    auto importerTest = new FilterImporterTest(&info);
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
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMailAppTest)

#include "moc_filtermailapptest.cpp"

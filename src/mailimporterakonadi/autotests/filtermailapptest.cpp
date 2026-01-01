/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filtermailapptest.h"
using namespace Qt::Literals::StringLiterals;

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
    filter.importMails(u"/foo/kde/bla/toto/"_s);
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMailAppTest)

#include "moc_filtermailapptest.cpp"

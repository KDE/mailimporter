/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filtermboxtest.h"
using namespace Qt::Literals::StringLiterals;

#include "filterimportertest.h"
#include <MailImporter/FilterMBox>
#include <QTest>

FilterMBoxTest::FilterMBoxTest(QObject *parent)
    : QObject(parent)
{
}

FilterMBoxTest::~FilterMBoxTest()
{
}

void FilterMBoxTest::shouldImportData()
{
}

void FilterMBoxTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterMBox filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterMBoxTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterMBox filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList() << u"/foo/kde/bla/toto/"_s);
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterMBoxTest)

#include "moc_filtermboxtest.cpp"

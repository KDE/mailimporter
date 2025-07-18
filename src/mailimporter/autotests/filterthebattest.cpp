/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterthebattest.h"
using namespace Qt::Literals::StringLiterals;

#include "filterimportertest.h"
#include <MailImporter/FilterTheBat>
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
    auto importerTest = new FilterImporterTest(&info);
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
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(u"/foo/kde/bla/toto/"_s);
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterTheBatTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterTheBat filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterTheBatTest)

#include "moc_filterthebattest.cpp"

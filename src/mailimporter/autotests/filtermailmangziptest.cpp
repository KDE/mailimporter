/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filtermailmangziptest.h"
#include <MailImporter/FilterMailmanGzip>
#include "filterimportertest.h"
#include <QTest>

FilterMAilmangzipTest::FilterMAilmangzipTest(QObject *parent)
    : QObject(parent)
{
}

FilterMAilmangzipTest::~FilterMAilmangzipTest()
{
}

void FilterMAilmangzipTest::shouldImportData()
{
}

void FilterMAilmangzipTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterMailmanGzip filter;
    MailImporter::FilterInfo info;
    auto *importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringList());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterMAilmangzipTest::canNotImportDataUnknowPath()
{
    //VERIFY it.
#if 0
    MailImporter::FilterMailmanGzip filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringList() << QStringLiteral("/foo/kde/bla/toto/bla.zip"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
#endif
}

QTEST_MAIN(FilterMAilmangzipTest)

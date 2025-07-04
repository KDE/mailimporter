/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterlnotestest.h"
using namespace Qt::Literals::StringLiterals;

#include "filterimportertest.h"
#include "filters/filterlnotes.h"
#include <QTest>

FilterLnotesTest::FilterLnotesTest(QObject *parent)
    : QObject(parent)
{
}

FilterLnotesTest::~FilterLnotesTest()
{
}

void FilterLnotesTest::shouldImportData()
{
}

void FilterLnotesTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterLNotes filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    // TODO implement it
    // filter.importMail(QString());
    // QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterLnotesTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterLNotes filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    // filter.importMails(u"/foo/kde/bla/toto/"_s);
    // QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterLnotesTest)

#include "moc_filterlnotestest.cpp"

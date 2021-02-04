/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "filtericedovetest.h"
#include "filterimportertest.h"
#include "filters/filtericedove.h"
#include <QTest>

class FilterIcecoveAbstract : public MailImporter::FilterIcedove
{
public:
    FilterIcecoveAbstract()
    {
    }

    QString settingsPath() override
    {
        return MailImporter::FilterIcedove::settingsPath();
    }
};

FilterIcedoveTest::FilterIcedoveTest(QObject *parent)
    : QObject(parent)
{
}

FilterIcedoveTest::~FilterIcedoveTest()
{
}

void FilterIcedoveTest::shouldHaveDefaultSettingsPath()
{
    FilterIcecoveAbstract filter;
    QCOMPARE(filter.settingsPath(), MailImporter::FilterIcedove::defaultSettingsPath());
}

void FilterIcedoveTest::shouldImportData()
{
}

void FilterIcedoveTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterIcedoveTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterIcedoveTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterIcedove filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterIcedoveTest)

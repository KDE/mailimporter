/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "filterthunderbirdtest.h"
using namespace Qt::Literals::StringLiterals;

#include "filterimportertest.h"
#include "filters/filterthunderbird.h"
#include <QTest>

class FilterThunderBirdAbstract : public MailImporter::FilterThunderbird
{
public:
    FilterThunderBirdAbstract()
    {
    }

    QString settingsPath() override
    {
        return MailImporter::FilterThunderbird::settingsPath();
    }
};

FilterThunderBirdTest::FilterThunderBirdTest(QObject *parent)
    : QObject(parent)
{
}

FilterThunderBirdTest::~FilterThunderBirdTest()
{
}

void FilterThunderBirdTest::shouldHaveDefaultSettingsPath()
{
    FilterThunderBirdAbstract filter;
    QCOMPARE(filter.settingsPath(), MailImporter::FilterThunderbird::defaultSettingsPath());
}

void FilterThunderBirdTest::shouldImportData()
{
}

void FilterThunderBirdTest::canNotImportDataEmptyPath()
{
    MailImporter::FilterThunderbird filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterThunderBirdTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterThunderbird filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(u"/foo/kde/bla/toto/"_s);
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

void FilterThunderBirdTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterThunderbird filter;
    MailImporter::FilterInfo info;
    auto importerTest = new FilterImporterTest(&info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(&info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
    delete importerTest;
}

QTEST_MAIN(FilterThunderBirdTest)

#include "moc_filterthunderbirdtest.cpp"

/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "filterclawsmailtest.h"
#include <MailImporter/FilterClawsMail>
#include "filterimportertest.h"
#include <qtest.h>

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
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QString());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterClawsMailTest::canNotImportDataUnknowPath()
{
    MailImporter::FilterClawsMail filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringLiteral("/foo/kde/bla/toto/"));
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

void FilterClawsMailTest::canNotImportDataWhenHomeDirSelected()
{
    MailImporter::FilterClawsMail filter;
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QDir::homePath());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
}

QTEST_MAIN(FilterClawsMailTest)

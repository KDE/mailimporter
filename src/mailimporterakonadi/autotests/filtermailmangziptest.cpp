/*
  Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

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

#include "filtermailmangziptest.h"
#include <MailImporter/FilterMailmanGzip>
#include "filterimportertest.h"
#include <qtest.h>

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
    MailImporter::FilterInfo *info = new MailImporter::FilterInfo;
    FilterImporterTest *importerTest = new FilterImporterTest(info);
    filter.setFilterImporter(importerTest);
    filter.setFilterInfo(info);
    filter.importMails(QStringList());
    QVERIFY(importerTest->filterImporterDataList().isEmpty());
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

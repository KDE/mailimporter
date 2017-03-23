/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

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

#include "messagestatustest.h"
#include <MailImporter/MessageStatus>
#include <QTest>

MessageStatusTest::MessageStatusTest(QObject *parent)
    : QObject(parent)
{

}

void MessageStatusTest::shouldHaveDefaultValues()
{
    MailImporter::MessageStatus status;
    QVERIFY(!status.isDeleted());
    QVERIFY(!status.isRead());
    QVERIFY(!status.isReplied());
    QVERIFY(!status.isForwarded());
}

void MessageStatusTest::shouldAssignValues_data()
{
    QTest::addColumn<bool>("isread");
    QTest::addColumn<bool>("isdeleted");
    QTest::addColumn<bool>("isreplied");
    QTest::addColumn<bool>("isforwarded");
    QTest::newRow("test1") << true << true << true << true;
    QTest::newRow("test2") << false << false << false << false;
    QTest::newRow("test3") << false << true << false << true;
    QTest::newRow("test4") << true << true << false << true;
    QTest::newRow("test5") << true << true << false << false;
}

void MessageStatusTest::shouldAssignValues()
{
    QFETCH(bool, isread);
    QFETCH(bool, isdeleted);
    QFETCH(bool, isreplied);
    QFETCH(bool, isforwarded);

    MailImporter::MessageStatus status;
    status.setDeleted(isdeleted);
    status.setRead(isread);
    status.setReplied(isreplied);
    status.setForwarded(isforwarded);

    QCOMPARE(status.isDeleted(), isdeleted);
    QCOMPARE(status.isRead(), isread);
    QCOMPARE(status.isReplied(), isreplied);
    QCOMPARE(status.isForwarded(), isforwarded);
}

QTEST_MAIN(MessageStatusTest)


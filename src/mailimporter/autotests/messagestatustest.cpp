/*
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
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

#include "moc_messagestatustest.cpp"

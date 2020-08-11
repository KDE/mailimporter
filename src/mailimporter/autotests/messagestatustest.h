/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MESSAGESTATUSTEST_H
#define MESSAGESTATUSTEST_H

#include <QObject>

class MessageStatusTest : public QObject
{
    Q_OBJECT
public:
    explicit MessageStatusTest(QObject *parent = nullptr);
    ~MessageStatusTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignValues();
    void shouldAssignValues_data();
};

#endif // MESSAGESTATUSTEST_H

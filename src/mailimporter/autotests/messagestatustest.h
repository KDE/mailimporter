/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

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

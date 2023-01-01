/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class SelectThunderbirdProfileDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectThunderbirdProfileDialogTest(QObject *parent = nullptr);
    ~SelectThunderbirdProfileDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

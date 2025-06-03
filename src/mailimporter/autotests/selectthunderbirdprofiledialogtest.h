/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
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

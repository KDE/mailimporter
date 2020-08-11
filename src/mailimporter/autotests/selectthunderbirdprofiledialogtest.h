/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SELECTTHUNDERBIRDPROFILEDIALOGTEST_H
#define SELECTTHUNDERBIRDPROFILEDIALOGTEST_H

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

#endif // SELECTTHUNDERBIRDPROFILEDIALOGTEST_H

/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class FilterThunderBirdTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterThunderBirdTest(QObject *parent = nullptr);
    ~FilterThunderBirdTest();
private Q_SLOTS:
    void shouldHaveDefaultSettingsPath();
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

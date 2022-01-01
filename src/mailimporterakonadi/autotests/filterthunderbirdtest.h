/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
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


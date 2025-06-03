/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class FilterIcedoveTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterIcedoveTest(QObject *parent = nullptr);
    ~FilterIcedoveTest();
private Q_SLOTS:
    void shouldHaveDefaultSettingsPath();
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

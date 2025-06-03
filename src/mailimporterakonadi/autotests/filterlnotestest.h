/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class FilterLnotesTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterLnotesTest(QObject *parent = nullptr);
    ~FilterLnotesTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};

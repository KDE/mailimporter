/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class FilterMailAppTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterMailAppTest(QObject *parent = nullptr);
    ~FilterMailAppTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};

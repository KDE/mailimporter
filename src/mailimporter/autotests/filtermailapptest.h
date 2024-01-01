/*
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
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

/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class FilterMBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterMBoxTest(QObject *parent = nullptr);
    ~FilterMBoxTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};

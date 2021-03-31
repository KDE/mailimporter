/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class FilterMAilmangzipTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterMAilmangzipTest(QObject *parent = nullptr);
    ~FilterMAilmangzipTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};


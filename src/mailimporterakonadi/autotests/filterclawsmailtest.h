/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERCLAWSMAILTEST_H
#define FILTERCLAWSMAILTEST_H

#include <QObject>

class FilterClawsMailTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterClawsMailTest(QObject *parent = nullptr);
    ~FilterClawsMailTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

#endif // FILTERCLAWSMAILTEST_H

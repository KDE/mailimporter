/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FilterTheBatTest_H
#define FilterTheBatTest_H

#include <QObject>

class FilterTheBatTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterTheBatTest(QObject *parent = nullptr);
    ~FilterTheBatTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

#endif // FilterTheBatTest_H

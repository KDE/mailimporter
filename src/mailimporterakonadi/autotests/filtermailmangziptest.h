/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FilterMAilmangzipTest_H
#define FilterMAilmangzipTest_H

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

#endif // FilterMAilmangzipTest_H

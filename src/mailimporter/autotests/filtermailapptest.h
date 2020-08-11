/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERMailAppTEST_H
#define FILTERMailAppTEST_H

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

#endif // FILTERMailAppTEST_H

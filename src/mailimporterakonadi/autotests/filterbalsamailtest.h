/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERBALSAMAILTEST_H
#define FILTERBALSAMAILTEST_H

#include <QObject>

class FilterBalsaMailTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterBalsaMailTest(QObject *parent = nullptr);
    ~FilterBalsaMailTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

#endif // FILTERBALSAMAILTEST_H

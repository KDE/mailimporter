/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERSYLPHEEDTEST_H
#define FILTERSYLPHEEDTEST_H

#include <QObject>

class FilterSylpheedTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterSylpheedTest(QObject *parent = nullptr);
    ~FilterSylpheedTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

#endif // FILTERSYLPHEEDTEST_H

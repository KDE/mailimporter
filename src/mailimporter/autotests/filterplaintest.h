/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERPLAINTEST_H
#define FILTERPLAINTEST_H

#include <QObject>

class FilterPlainTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterPlainTest(QObject *parent = nullptr);
    ~FilterPlainTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};

#endif // FILTERPLAINTEST_H

/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERLnotesTEST_H
#define FILTERLnotesTEST_H

#include <QObject>

class FilterLnotesTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterLnotesTest(QObject *parent = nullptr);
    ~FilterLnotesTest();
private Q_SLOTS:
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
};

#endif // FILTERLnotesTEST_H

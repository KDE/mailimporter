/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef FILTERTHUNDERBIRDTEST_H
#define FILTERTHUNDERBIRDTEST_H

#include <QObject>

class FilterThunderBirdTest : public QObject
{
    Q_OBJECT
public:
    explicit FilterThunderBirdTest(QObject *parent = nullptr);
    ~FilterThunderBirdTest();
private Q_SLOTS:
    void shouldHaveDefaultSettingsPath();
    void shouldImportData();
    void canNotImportDataEmptyPath();
    void canNotImportDataUnknowPath();
    void canNotImportDataWhenHomeDirSelected();
};

#endif // FILTERTHUNDERBIRDTEST_H

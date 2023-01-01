/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QString>

class FilterImporterTestUtil
{
public:
    explicit FilterImporterTestUtil(const QString &filename);
    QString extractData();

private:
    QString mFileName;
};

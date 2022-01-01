/*
  SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

class FilterImporterTestUtil
{
public:
    FilterImporterTestUtil(const QString &filename);
    QString extractData();

private:
    QString mFileName;
};


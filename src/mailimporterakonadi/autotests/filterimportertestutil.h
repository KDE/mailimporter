/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
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

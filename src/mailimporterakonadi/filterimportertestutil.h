/*
  SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FILTERIMPORTERTESTUTIL_H
#define FILTERIMPORTERTESTUTIL_H

#include <QString>

class FilterImporterTestUtil
{
public:
    FilterImporterTestUtil(const QString &filename);
    QString extractData();
private:
    QString mFileName;
};

#endif // FILTERIMPORTERTESTUTIL_H

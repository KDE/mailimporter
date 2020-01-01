/*
  Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "filterimporterbase.h"
#include <MailImporter/FilterInfo>

using namespace MailImporter;

FilterImporterBase::FilterImporterBase(MailImporter::FilterInfo *info)
    : mInfo(info)
{
}

FilterImporterBase::~FilterImporterBase()
{
}

bool FilterImporterBase::importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MessageStatus &status)
{
    Q_UNUSED(folderName);
    Q_UNUSED(msgPath);
    Q_UNUSED(duplicateCheck);
    Q_UNUSED(status);
    return false;
}

bool FilterImporterBase::importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone)
{
    Q_UNUSED(file);
    Q_UNUSED(folderPath);
    Q_UNUSED(nbTotal);
    Q_UNUSED(fileDone);
    return false;
}

void FilterImporterBase::clear()
{
}

void FilterImporterBase::clearCountDuplicate()
{
}

int FilterImporterBase::countDuplicates() const
{
    return -1;
}

QString FilterImporterBase::topLevelFolder() const
{
    return {};
}

/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
    Q_UNUSED(folderName)
    Q_UNUSED(msgPath)
    Q_UNUSED(duplicateCheck)
    Q_UNUSED(status)
    return false;
}

bool FilterImporterBase::importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone)
{
    Q_UNUSED(file)
    Q_UNUSED(folderPath)
    Q_UNUSED(nbTotal)
    Q_UNUSED(fileDone)
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

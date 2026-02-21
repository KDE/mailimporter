/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

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

bool FilterImporterBase::importMessage([[maybe_unused]] const QString &folderName,
                                       [[maybe_unused]] const QString &msgPath,
                                       [[maybe_unused]] bool duplicateCheck,
                                       [[maybe_unused]] const MessageStatus &status)
{
    return false;
}

bool FilterImporterBase::importMessage([[maybe_unused]] const KArchiveFile *file,
                                       [[maybe_unused]] const QString &folderPath,
                                       [[maybe_unused]] int &nbTotal,
                                       [[maybe_unused]] int &fileDone)
{
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

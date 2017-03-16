/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef FILTERIMPORTERAKONADI_H
#define FILTERIMPORTERAKONADI_H

#include <MailImporter/FilterImporterBase>
#include "mailimporter_export.h"
#include <QString>
class MAILIMPORTER_EXPORT FilterImporterAkonadi : public MailImporter::FilterImporterBase
{
public:
    FilterImporterAkonadi();
    ~FilterImporterAkonadi();

    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status) Q_DECL_OVERRIDE;
};

#endif // FILTERIMPORTERAKONADI_H

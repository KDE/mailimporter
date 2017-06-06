/*
  Copyright (c) 2012-2017 Montel Laurent <montel@kde.org>

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

#ifndef MAILIMPORTER_FILTER_CLAWSMAILS_H
#define MAILIMPORTER_FILTER_CLAWSMAILS_H

#include <QHash>

#include "filtersylpheed.h"
/**
 * Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * @author Danny Kukawka
 */
namespace MailImporter {
class MAILIMPORTER_EXPORT FilterClawsMail : public FilterSylpheed
{
public:
    FilterClawsMail();
    ~FilterClawsMail();

    static QString defaultSettingsPath();

    /* return local mail dir from folderlist.xml*/
    QString localMailDirPath() override;
    bool excludeFile(const QString &file) override;
    QString defaultInstallFolder() const override;
    QString markFile() const override;
};
}

#endif

/*
  Copyright (c) 2012-2018 Montel Laurent <montel@kde.org>

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

#ifndef FILTERBALSA_H
#define FILTERBALSA_H

#include "filters.h"
namespace MailImporter {
class FilterBalsaPrivate;
class MAILIMPORTER_EXPORT FilterBalsa : public Filter
{
public:
    FilterBalsa();
    ~FilterBalsa();

    void import() override;
    void importMails(const QString &maildir);
    static QString defaultSettingsPath();
    static QString isMailerFound();
    QString localMailDirPath();
private:
    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    FilterBalsaPrivate *const d;
};
}

#endif // FILTERBALSA_H

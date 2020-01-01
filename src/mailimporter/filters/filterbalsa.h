/*
  Copyright (c) 2012-2020 Laurent Montel <montel@kde.org>

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

#ifndef FILTERBALSA_H
#define FILTERBALSA_H

#include "filters.h"
namespace MailImporter {
class FilterBalsaPrivate;
/**
 * @brief The FilterBalsa class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterBalsa : public Filter
{
public:
    FilterBalsa();
    ~FilterBalsa() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();
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

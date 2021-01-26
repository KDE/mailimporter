/*
  filterthebat.h  -  TheBat! mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_THEBAT_H
#define MAILIMPORTER_FILTER_THEBAT_H

#include "filters.h"
#include "mailimporter_export.h"
namespace MailImporter
{
class FilterTheBatPrivate;
/**
 * Imports The Bat! mail folder recursively, recreating the folder structure.
 * @author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterTheBat : public Filter
{
public:
    FilterTheBat();
    ~FilterTheBat() override;

    void import() override;
    void importMails(const QString &maildir);

private:
    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);
    FilterTheBatPrivate *const d;
};
}

#endif

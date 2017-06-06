/***************************************************************************
            filter_thebat.h  -  TheBat! mail import
                             -------------------
    begin                : April 07 2005
    copyright            : (C) 2005 by Danny Kukawka
    email                : danny.kukawka@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/* Copyright (c) 2012-2017 Montel Laurent <montel@kde.org>                      */

#ifndef MAILIMPORTER_FILTER_THEBAT_H
#define MAILIMPORTER_FILTER_THEBAT_H

#include "filters.h"
#include "mailimporter_export.h"
/**
 * Imports The Bat! mail folder recursively, recreating the folder structure.
 * @author Danny Kukawka
 */
namespace MailImporter {
class FilterTheBatPrivate;
class MAILIMPORTER_EXPORT FilterTheBat : public Filter
{
public:
    FilterTheBat();
    ~FilterTheBat();

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

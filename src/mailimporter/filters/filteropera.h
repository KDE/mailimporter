/***************************************************************************
                  filter_opera.h  -  Opera mail import
                             -------------------
    begin                : Januar 26 2005
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

#ifndef MAILIMPORTER_FILTER_OPERA_H
#define MAILIMPORTER_FILTER_OPERA_H

#include "filters.h"
#include <QDir>
namespace MailImporter {
/**
 *imports opera account-archives into KMail
 *@author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterOpera : public Filter
{
public:
    FilterOpera();
    ~FilterOpera() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();

private:
    void importBox(const QDir &importDir, const QStringList &, const QString &accountName = QString());
    void importRecursive(const QDir &maildir, const QString &accountName = QString());
};
}

#endif

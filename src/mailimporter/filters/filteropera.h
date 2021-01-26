/*
  filteropera.h  -  Opera mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_OPERA_H
#define MAILIMPORTER_FILTER_OPERA_H

#include "filters.h"
#include <QDir>
namespace MailImporter
{
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

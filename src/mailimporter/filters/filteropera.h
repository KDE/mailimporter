/*
  filteropera.h  -  Opera mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString isMailerFound();

private:
    MAILIMPORTER_NO_EXPORT void importBox(const QDir &importDir, const QStringList &, const QString &accountName = QString());
    MAILIMPORTER_NO_EXPORT void importRecursive(const QDir &maildir, const QString &accountName = QString());
};
}

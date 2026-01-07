/*
  filterkmail_maildir.h  -  Kmail maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
class FilterKMail_maildirPrivate;
/*!
 * Imports KMail mail folder with maildir format recursively, recreating the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterKMail_maildir : public Filter
{
public:
    FilterKMail_maildir();
    ~FilterKMail_maildir() override;

    void import() override;
    void importMails(const QString &maildir);

private:
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);

    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    std::unique_ptr<FilterKMail_maildirPrivate> const d;
};
}

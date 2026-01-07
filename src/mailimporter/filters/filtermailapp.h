/*
  filtermailapp.h  -  OS X Mail App import

  SPDX-FileCopyrightText: 2004 Chris Howells <howells@kde.org>
  Derived from code by:
  SPDX-FileCopyrightText: 2003 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
class FilterMailAppPrivate;
/*!
 *imports mbox archives messages into KMail
 *\author Chris Howells
 */
class MAILIMPORTER_EXPORT FilterMailApp : public Filter
{
public:
    /*!
     */
    FilterMailApp();
    /*!
     */
    ~FilterMailApp() override;

    /*!
     */
    void import() override;
    /*!
     */
    void importMails(const QString &maildir);

private:
    std::unique_ptr<FilterMailAppPrivate> const d;
    MAILIMPORTER_NO_EXPORT void traverseDirectory(const QString &);
};
}

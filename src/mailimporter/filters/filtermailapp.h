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
 * \class MailImporter::FilterMailApp
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterMailApp
 *
 * \brief FilterMailApp imports mbox archives messages into KMail.
 * \author Chris Howells
 */
class MAILIMPORTER_EXPORT FilterMailApp : public Filter
{
public:
    /*!
     * \brief Constructor for FilterMailApp.
     */
    FilterMailApp();
    /*!
     * \brief Destructor for FilterMailApp.
     */
    ~FilterMailApp() override;

    /*!
     * \brief Imports Mail.app mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);

private:
    std::unique_ptr<FilterMailAppPrivate> const d;
    MAILIMPORTER_NO_EXPORT void traverseDirectory(const QString &);
};
}

/*
  filtermbox.h  -  mbox mail import

  SPDX-FileCopyrightText: 2003 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/*!
 * \class MailImporter::FilterMBox
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterMBox
 *
 * \brief The FilterMBox class imports mbox archives messages into KMail.
 * \author Laurence Anderson
 */
class MAILIMPORTER_EXPORT FilterMBox : public Filter
{
public:
    /*!
     * \brief Constructor for FilterMBox.
     */
    FilterMBox();
    /*!
     * \brief Destructor for FilterMBox.
     */
    ~FilterMBox() override;

    /*!
     * \brief Imports mails from the specified mbox files.
     * \param filenames List of mbox files to import
     */
    void importMails(const QStringList &filenames);
    /*!
     * \brief Imports mbox mail archives.
     */
    void import() override;
};
}

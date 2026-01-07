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
 * \brief imports mbox archives messages into KMail
 * \author Laurence Anderson
 */
class MAILIMPORTER_EXPORT FilterMBox : public Filter
{
public:
    /*!
     */
    FilterMBox();
    /*!
     */
    ~FilterMBox() override;

    /*!
     */
    void importMails(const QStringList &filenames);
    /*!
     */
    void import() override;
};
}

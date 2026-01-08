/*
  filterplain.h  -  Plain mail import

  SPDX-FileCopyrightText: 2002 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
/*!
 * \class MailImporter::FilterPlain
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterPlain
 *
 * \brief imports Plain text messages into KMail.
 * \author laurence
 */
class MAILIMPORTER_EXPORT FilterPlain : public Filter
{
public:
    /*!
     */
    FilterPlain();
    /*!
     */
    ~FilterPlain() override;

    /*!
     */
    void import() override;
    /*!
     */
    void importMails(const QString &mailDir);
};
}

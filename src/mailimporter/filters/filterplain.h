/*
  filterplain.h  -  Plain mail import

  SPDX-FileCopyrightText: 2002 Laurence Anderson <l.d.anderson@warwick.ac.uk>

  SPDX-License-Identifier: GPL-2.0-or-later
*/


#ifndef MAILIMPORTER_FILTER_PLAIN_H
#define MAILIMPORTER_FILTER_PLAIN_H

#include "filters.h"
namespace MailImporter {
/**
 *imports Plain text messages into KMail
 *@author laurence
 */
class MAILIMPORTER_EXPORT FilterPlain : public Filter
{
public:
    FilterPlain();
    ~FilterPlain() override;

    void import() override;
    void importMails(const QString &mailDir);
};
}

#endif

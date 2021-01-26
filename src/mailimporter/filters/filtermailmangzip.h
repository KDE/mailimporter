/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_MAILMANGZIP_H
#define MAILIMPORTER_FILTER_MAILMANGZIP_H

#include "filters.h"

namespace MailImporter
{
/**
 * @brief The FilterMailmanGzip class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterMailmanGzip : public Filter
{
public:
    FilterMailmanGzip();
    ~FilterMailmanGzip() override;

    void importMails(const QStringList &filenames);
    void import() override;
};
}

#endif

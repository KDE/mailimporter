/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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

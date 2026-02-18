/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/*!
 * \class MailImporter::FilterMailmanGzip
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterMailmanGzip
 *
 * \brief The FilterMailmanGzip class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterMailmanGzip : public Filter
{
public:
    /*!
     * \brief Constructor for FilterMailmanGzip.
     */
    FilterMailmanGzip();
    /*!
     * \brief Destructor for FilterMailmanGzip.
     */
    ~FilterMailmanGzip() override;

    /*!
     * \brief Imports mails from the specified gzip archive files.
     * \param filenames List of gzip archive files to import
     */
    void importMails(const QStringList &filenames);
    /*!
     * \brief Imports mailman gzip archives.
     */
    void import() override;
};
}

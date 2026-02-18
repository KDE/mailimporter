/*
  filterthebat.h  -  TheBat! mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
#include "mailimporter_export.h"
namespace MailImporter
{
class FilterTheBatPrivate;
/*!
 * \class MailImporter::FilterTheBat
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterTheBat
 *
 * \brief Imports The Bat! mail folder recursively, recreating the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterTheBat : public Filter
{
public:
    /*!
     * \brief Constructor for FilterTheBat.
     */
    FilterTheBat();

    /*!
     * \brief Destructor for FilterTheBat.
     */
    ~FilterTheBat() override;

    /*!
     * \brief Imports The Bat! mail folders.
     */
    void import() override;

    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The mail directory to import from
     */
    void importMails(const QString &maildir);

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);
    std::unique_ptr<FilterTheBatPrivate> const d;
};
}

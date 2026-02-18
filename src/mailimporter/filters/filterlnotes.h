/*
  filterlnotes.h  -  Lotus Notes Structured Text mail import

  SPDX-FileCopyrightText: 2005 Robert Rockers <kconfigure@rockerssoft.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"
namespace MailImporter
{
class FilterLNotesPrivate;
/*!
 * \class MailImporter::FilterLNotes
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterLNotes
 *
 * \brief imports Lotus Notes Structured Text Archives and archives messages into KMail.
 * \author Robert Rockers
 */
class MAILIMPORTER_EXPORT FilterLNotes : public Filter
{
public:
    /*!
     * \brief Constructor for FilterLNotes.
     */
    FilterLNotes();
    /*!
     * \brief Destructor for FilterLNotes.
     */
    ~FilterLNotes() override;
    /*!
     * \brief Standard import filter, starting line for import.
     */
    void import() override;

private:
    std::unique_ptr<FilterLNotesPrivate> const d;
    /*!
     * This is were all the real action is gonna be handled.
     * Gets called once for EACH file imported
     */
    MAILIMPORTER_NO_EXPORT void ImportLNotes(const QString &file);
};
}

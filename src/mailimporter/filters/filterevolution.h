/*
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_EVOLUTION_H
#define MAILIMPORTER_FILTER_EVOLUTION_H

#include "filters.h"
namespace MailImporter {
/**
 * Imports Evolution mboxes recursively, keeping the folder structure.
 * @author Simon MARTIN
 */
class MAILIMPORTER_EXPORT FilterEvolution : public Filter
{
public:
    FilterEvolution();
    ~FilterEvolution() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();
private:
    void importDirContents(const QString &, const QString &, const QString &);
    void importMBox(const QString &, const QString &, const QString &);
};
}

#endif

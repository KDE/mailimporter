/*
  filterevolution_v2.h  -  Evolution 2.0.x mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  Inspired and partly copied from filterevolution
  SPDX-FileCopyrightText: 2004 Simon MARTIN <simartin@users.sourceforge.net>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_EVOLUTION_V2_H
#define MAILIMPORTER_FILTER_EVOLUTION_V2_H

#include "filters.h"

namespace MailImporter {
/**
 * Imports Evolution v2.x mail folder recursively, keeping the folder structure.
 * @author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterEvolution_v2 : public Filter
{
public:
    FilterEvolution_v2();
    ~FilterEvolution_v2() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();

private:
    void importDirContents(const QString &, const QString &, const QString &);
    void importMBox(const QString &, const QString &, const QString &);
    Q_REQUIRED_RESULT bool excludeFiles(const QString &file);
};
}

#endif

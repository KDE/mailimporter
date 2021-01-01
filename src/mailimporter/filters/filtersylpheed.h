/*
  filtersylpheed.h  -  Sylpheed maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_SYLPHEED_H
#define MAILIMPORTER_FILTER_SYLPHEED_H

#include <QHash>

#include "filters.h"
namespace MailImporter {
class FilterSylpheedPrivate;
/**
 * Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * @author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterSylpheed : public Filter
{
public:
    FilterSylpheed();
    ~FilterSylpheed() override;

    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();

    void import() override;
    virtual void importMails(const QString &maildir);

    /* return local mail dir from folderlist.xml*/
    virtual QString localMailDirPath();
    Q_REQUIRED_RESULT virtual bool excludeFile(const QString &file);
    virtual QString defaultInstallFolder() const;
    virtual QString markFile() const;
private:

    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);

    void readMarkFile(const QString &, QHash<QString, unsigned long> &);
    MailImporter::MessageStatus msgFlagsToString(unsigned long flags);
    FilterSylpheedPrivate *const d;
};
}

#endif

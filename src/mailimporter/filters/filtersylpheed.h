/*
  filtersylpheed.h  -  Sylpheed maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>

#include "filters.h"
namespace MailImporter
{
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

    [[nodiscard]] static QString defaultSettingsPath();
    [[nodiscard]] static QString isMailerFound();

    void import() override;
    virtual void importMails(const QString &maildir);

    /* return local mail dir from folderlist.xml*/
    virtual QString localMailDirPath();
    [[nodiscard]] virtual bool excludeFile(const QString &file);
    virtual QString defaultInstallFolder() const;
    virtual QString markFile() const;

private:
    MAILIMPORTER_NO_EXPORT void importDirContents(const QString &);
    MAILIMPORTER_NO_EXPORT void importFiles(const QString &);
    MAILIMPORTER_NO_EXPORT void processDirectory(const QString &path);

    MAILIMPORTER_NO_EXPORT void readMarkFile(const QString &, QHash<QString, unsigned long> &);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT MailImporter::MessageStatus msgFlagsToString(unsigned long flags);
    std::unique_ptr<FilterSylpheedPrivate> const d;
};
}

/*
  filtersylpheed.h  -  Sylpheed maildir mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>

#include "filters.h"
namespace MailImporter
{
class FilterSylpheedPrivate;
/*!
 * \class MailImporter::FilterSylpheed
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterSylpheed
 *
 * \brief Imports Sylpheed mail folder with maildir format recursively, recreating the folder structure.
 * \author Danny Kukawka
 */
class MAILIMPORTER_EXPORT FilterSylpheed : public Filter
{
public:
    /*!
     * \brief Constructor for FilterSylpheed.
     */
    FilterSylpheed();
    /*!
     * \brief Destructor for FilterSylpheed.
     */
    ~FilterSylpheed() override;

    /*!
     * \brief Returns the default settings path for Sylpheed.
     * \return The default settings path
     */
    [[nodiscard]] static QString defaultSettingsPath();
    /*!
     * \brief Checks if Sylpheed mail client is found on the system.
     * \return A status message indicating if Sylpheed was found
     */
    [[nodiscard]] static QString isMailerFound();

    /*!
     * \brief Imports Sylpheed mail folders.
     */
    void import() override;
    /*!
     * \brief Imports mails from the specified directory.
     * \param maildir The maildir directory to import from
     */
    virtual void importMails(const QString &maildir);

    /* return local mail dir from folderlist.xml*/
    /*!
     * \brief Returns the local mail directory path.
     * \return The local mail directory path
     */
    virtual QString localMailDirPath();
    /*!
     * \brief Checks if a file should be excluded from import.
     * \param file The file path to check
     * \return True if the file should be excluded
     */
    [[nodiscard]] virtual bool excludeFile(const QString &file);
    /*!
     * \brief Returns the default installation folder for Sylpheed.
     * \return The default installation folder
     */
    virtual QString defaultInstallFolder() const;
    /*!
     * \brief Returns the mark file path.
     * \return The mark file path
     */
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

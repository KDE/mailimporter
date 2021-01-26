/*
   SPDX-FileCopyrightText: 2009, 2010 Klarälvdalens Datakonsult AB

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MAILIMPORTER_FILTER_KMAIL_ARCHIVE_H
#define MAILIMPORTER_FILTER_KMAIL_ARCHIVE_H

#include "filters.h"

class KArchiveFile;
class KArchiveDirectory;

namespace MailImporter
{
class FilterKMailArchivePrivate;
/**
 * @brief The FilterKMailArchive class
 */
class MAILIMPORTER_EXPORT FilterKMailArchive : public Filter
{
public:
    FilterKMailArchive();
    ~FilterKMailArchive() override;

    void import() override;
    void importMails(const QString &archiveFile);

private:
    Q_REQUIRED_RESULT bool importDirectory(const KArchiveDirectory *directory, const QString &folderPath);
    Q_REQUIRED_RESULT bool importFolder(const KArchiveDirectory *folder, const QString &folderPath);
    Q_REQUIRED_RESULT bool importMessage(const KArchiveFile *file, const QString &folderPath);

    int countFiles(const KArchiveDirectory *directory) const;
    FilterKMailArchivePrivate *const d;
};
}

#endif

/*
   SPDX-FileCopyrightText: 2009, 2010 Klarälvdalens Datakonsult AB

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

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
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool importDirectory(const KArchiveDirectory *directory, const QString &folderPath);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool importFolder(const KArchiveDirectory *folder, const QString &folderPath);
    [[nodiscard]] MAILIMPORTER_NO_EXPORT bool importMessage(const KArchiveFile *file, const QString &folderPath);

    [[nodiscard]] MAILIMPORTER_NO_EXPORT int countFiles(const KArchiveDirectory *directory) const;
    std::unique_ptr<FilterKMailArchivePrivate> const d;
};
}

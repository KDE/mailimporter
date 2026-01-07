/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#ifndef MAX_LINE
#define MAX_LINE 4096
#endif

#include "filterinfo.h"
#include "mailimporter_export.h"

#include <MailImporter/FilterImporterBase>

#include <QDir>
#include <memory>

namespace MailImporter
{
/*!
 * \brief The Filter class
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT Filter
{
public:
    /*!
     */
    explicit Filter(const QString &name, const QString &author, const QString &info = QString());
    /*!
     */
    virtual ~Filter();
    /*!
     */
    virtual void import() = 0;

    /*!
     */
    [[nodiscard]] QString author() const;
    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    [[nodiscard]] QString info() const;

    /*!
     */
    void setAuthor(const QString &);
    /*!
     */
    void setName(const QString &);
    /*!
     */
    void setInfo(const QString &);

    /*!
     */
    void clear();
    /*!
     */
    void setFilterInfo(MailImporter::FilterInfo *info);

    /*!
     */
    MailImporter::FilterInfo *filterInfo() const;

    /*!
     */
    void setFilterImporter(MailImporter::FilterImporterBase *importer);
    /*!
     */
    MailImporter::FilterImporterBase *filterImporter() const;

    /*!
     */
    void clearCountDuplicate();
    /*!
     */
    [[nodiscard]] int countDuplicates() const;

    /*!
     */
    void setMailDir(const QString &mailDir);
    /*!
     */
    [[nodiscard]] QString mailDir() const;

protected:
    /*!
     */
    static int countDirectory(const QDir &dir, bool searchHiddenDirectory);
    /*!
     */
    [[nodiscard]] bool
    importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MessageStatus &status = MailImporter::MessageStatus());

private:
    class FilterPrivate;
    std::unique_ptr<FilterPrivate> const d;
};
}

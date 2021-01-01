/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FILTERS_H
#define FILTERS_H

#ifndef MAX_LINE
#define MAX_LINE 4096
#endif

#include "filterinfo.h"
#include "filters.h"
#include "mailimporter_export.h"

#include <MailImporter/FilterImporterBase>

#include <QDir>

namespace MailImporter {
/**
 * @brief The Filter class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT Filter
{
public:
    explicit Filter(const QString &name, const QString &author, const QString &info = QString());
    virtual ~Filter();
    virtual void import() = 0;

    Q_REQUIRED_RESULT QString author() const;
    Q_REQUIRED_RESULT QString name() const;
    Q_REQUIRED_RESULT QString info() const;

    void setAuthor(const QString &);
    void setName(const QString &);
    void setInfo(const QString &);

    void clear();
    void setFilterInfo(MailImporter::FilterInfo *info);

    MailImporter::FilterInfo *filterInfo() const;

    void setFilterImporter(MailImporter::FilterImporterBase *importer);
    MailImporter::FilterImporterBase *filterImporter() const;

    void clearCountDuplicate();
    Q_REQUIRED_RESULT int countDuplicates() const;

    void setMailDir(const QString &mailDir);
    Q_REQUIRED_RESULT QString mailDir() const;

protected:
    static int countDirectory(const QDir &dir, bool searchHiddenDirectory);
    Q_REQUIRED_RESULT bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MessageStatus &status = MailImporter::MessageStatus());
private:
    class Private;
    Private *const d;
};
}

#endif

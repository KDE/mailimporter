/***************************************************************************
                          filters.h  -  description
                             -------------------
    begin                : Fri Jun 30 2000
    copyright            : (C) 2000 by Hans Dijkema
    email                : kmailcvt@hum.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/* Copyright (c) 2012-2019 Montel Laurent <montel@kde.org>                      */

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
    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, MailImporter::MessageStatus status = MailImporter::MessageStatus());
private:
    class Private;
    Private *const d;
};
}

#endif

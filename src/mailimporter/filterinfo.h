#ifndef FILTERINFO_H
#define FILTERINFO_H

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
/* Copyright (c) 2012-2020 Laurent Montel <montel@kde.org>                      */

#include "mailimporter_export.h"
#include <QString>
#include <QWidget>
namespace MailImporter {
class FilterInfoGui;
/**
 * @brief The FilterInfo class
 */
class MAILIMPORTER_EXPORT FilterInfo
{
public:
    FilterInfo();
    ~FilterInfo();

    void setFilterInfoGui(FilterInfoGui *filterinfogui);

    void setStatusMessage(const QString &status);
    void setFrom(const QString &from);
    void setTo(const QString &to);
    void setCurrent(const QString &current);
    void setCurrent(int percent = 0);
    void setOverall(int percent = 0);
    void addInfoLogEntry(const QString &log);
    void addErrorLogEntry(const QString &log);
    void clear();
    void alert(const QString &message);

    static void terminateASAP();
    Q_REQUIRED_RESULT bool shouldTerminate() const;
    Q_REQUIRED_RESULT QString rootCollectionName() const;

    QWidget *parentWidget() const;
    void setRemoveDupMessage(bool removeDupMessage);
    Q_REQUIRED_RESULT bool removeDupMessage() const;

private:
    class Private;
    Private *const d;
};
}

#endif /* FILTERINFO_H */

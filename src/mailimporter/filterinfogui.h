/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/**
 * @brief The FilterInfoGui class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterInfoGui
{
public:
    explicit FilterInfoGui();
    virtual ~FilterInfoGui();
    virtual void setStatusMessage(const QString &status);
    virtual void setFrom(const QString &from);
    virtual void setTo(const QString &to);
    virtual void setCurrent(const QString &current);
    virtual void setCurrent(int percent = 0);
    virtual void setOverall(int percent = 0);

    virtual void addInfoLogEntry(const QString &log);
    virtual void addErrorLogEntry(const QString &log);

    virtual void clear();
    virtual void alert(const QString &message);
    virtual QWidget *parent() const;
};
}


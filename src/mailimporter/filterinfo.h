/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"
#include <QString>
#include <memory>
class QWidget;
namespace MailImporter
{
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

    QWidget *parentWidget() const;
    void setRemoveDupMessage(bool removeDupMessage);
    Q_REQUIRED_RESULT bool removeDupMessage() const;

private:
    class FilterInfoPrivate;
    std::unique_ptr<FilterInfoPrivate> const d;
};
}

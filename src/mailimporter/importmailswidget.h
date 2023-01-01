/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mailimporter_export.h"
#include <QWidget>
class QListWidgetItem;
namespace MailImporter
{
class ImportMailsWidgetPrivate;
/**
 * @brief The ImportMailsWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT ImportMailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportMailsWidget(QWidget *parent = nullptr);
    ~ImportMailsWidget();

    void setStatusMessage(const QString &status);
    void setFrom(const QString &from);
    void setTo(const QString &to);
    void setCurrent(const QString &current);
    void setCurrent(int percent);
    void setOverall(int percent);
    void addItem(QListWidgetItem *item);
    void setLastCurrentItem();
    void clear();
    void addInfoLogEntry(const QString &log);
    void addErrorLogEntry(const QString &log);

private:
    std::unique_ptr<ImportMailsWidgetPrivate> const d;
};
}

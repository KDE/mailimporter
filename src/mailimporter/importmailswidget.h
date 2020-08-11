/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef IMPORTMAILSWIDGET_H
#define IMPORTMAILSWIDGET_H

#include <QWidget>
#include "mailimporter_export.h"
class QListWidgetItem;
namespace MailImporter {
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
    ImportMailsWidgetPrivate *const d;
};
}

#endif // IMPORTMAILSWIDGET_H

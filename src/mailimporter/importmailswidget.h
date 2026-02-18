/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mailimporter_export.h"
#include <QWidget>
class QListWidgetItem;
namespace MailImporter
{
class ImportMailsWidgetPrivate;
/*!
 * \class MailImporter::ImportMailsWidget
 * \inmodule MailImporter
 * \inheaderfile MailImporter/ImportMailsWidget
 *
 * \brief The ImportMailsWidget class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT ImportMailsWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor for ImportMailsWidget.
     * \param parent The parent widget
     */
    explicit ImportMailsWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for ImportMailsWidget.
     */
    ~ImportMailsWidget() override;

    /*!
     * \brief Sets the status message displayed in the widget.
     * \param status The status message
     */
    void setStatusMessage(const QString &status);
    /*!
     * \brief Sets the "from" source location.
     * \param from The source location
     */
    void setFrom(const QString &from);
    /*!
     * \brief Sets the "to" destination location.
     * \param to The destination location
     */
    void setTo(const QString &to);
    /*!
     * \brief Sets the current item description.
     * \param current The current item description
     */
    void setCurrent(const QString &current);
    /*!
     * \brief Sets the current progress as a percentage.
     * \param percent The progress percentage (0-100)
     */
    void setCurrent(int percent);
    /*!
     * \brief Sets the overall progress as a percentage.
     * \param percent The overall progress percentage (0-100)
     */
    void setOverall(int percent);
    /*!
     * \brief Adds an item to the import list widget.
     * \param item The list widget item to add
     */
    void addItem(QListWidgetItem *item);
    /*!
     * \brief Sets the last item as the current item in the list.
     */
    void setLastCurrentItem();
    /*!
     * \brief Clears all items from the widget.
     */
    void clear();
    /*!
     * \brief Adds an informational log entry.
     * \param log The log message to add
     */
    void addInfoLogEntry(const QString &log);
    /*!
     * \brief Adds an error log entry.
     * \param log The error message to add
     */
    void addErrorLogEntry(const QString &log);

private:
    std::unique_ptr<ImportMailsWidgetPrivate> const d;
};
}

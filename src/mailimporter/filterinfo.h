/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class MailImporter::FilterInfo
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterInfo
 *
 * \brief The FilterInfo class.
 */
class MAILIMPORTER_EXPORT FilterInfo
{
public:
    /*!
     * \brief Constructs a FilterInfo object.
     */
    FilterInfo();
    /*!
     * \brief Destructor for FilterInfo.
     */
    ~FilterInfo();

    /*!
     * \brief Sets the FilterInfoGui object for displaying progress.
     * \param filterinfogui The FilterInfoGui object
     */
    void setFilterInfoGui(FilterInfoGui *filterinfogui);

    /*!
     * \brief Sets the status message.
     * \param status The status message to display
     */
    void setStatusMessage(const QString &status);
    /*!
     * \brief Sets the source location.
     * \param from The source location
     */
    void setFrom(const QString &from);
    /*!
     * \brief Sets the destination location.
     * \param to The destination location
     */
    void setTo(const QString &to);
    /*!
     * \brief Sets the current item description.
     * \param current The current item being processed
     */
    void setCurrent(const QString &current);
    /*!
     * \brief Sets the current progress percentage.
     * \param percent The progress percentage (default 0)
     */
    void setCurrent(int percent = 0);
    /*!
     * \brief Sets the overall progress percentage.
     * \param percent The overall progress percentage (default 0)
     */
    void setOverall(int percent = 0);
    /*!
     * \brief Adds an informational log entry.
     * \param log The informational message to log
     */
    void addInfoLogEntry(const QString &log);
    /*!
     * \brief Adds an error log entry.
     * \param log The error message to log
     */
    void addErrorLogEntry(const QString &log);
    /*!
     * \brief Clears all logged entries and progress.
     */
    void clear();
    /*!
     * \brief Shows an alert dialog with the given message.
     * \param message The alert message
     */
    void alert(const QString &message);

    /*!
     * \brief Signals that import should terminate as soon as possible.
     */
    static void terminateASAP();
    /*!
     * \brief Returns whether termination has been requested.
     * \return True if termination has been requested
     */
    [[nodiscard]] bool shouldTerminate() const;

    /*!
     * \brief Returns the parent widget.
     * \return The parent widget
     */
    QWidget *parentWidget() const;
    /*!
     * \brief Sets whether duplicate messages should be removed.
     * \param removeDupMessage True to remove duplicates
     */
    void setRemoveDupMessage(bool removeDupMessage);
    /*!
     * \brief Returns whether duplicate messages should be removed.
     * \return True if duplicates should be removed
     */
    [[nodiscard]] bool removeDupMessage() const;

private:
    class FilterInfoPrivate;
    std::unique_ptr<FilterInfoPrivate> const d;
};
}

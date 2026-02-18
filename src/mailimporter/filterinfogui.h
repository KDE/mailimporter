/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "filters.h"

namespace MailImporter
{
/*!
 * \class MailImporter::FilterInfoGui
 * \inmodule MailImporter
 * \inheaderfile MailImporter/FilterInfoGui
 *
 * \brief The FilterInfoGui class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterInfoGui
{
public:
    /*!
     * \brief Constructs a FilterInfoGui.
     */
    explicit FilterInfoGui();
    /*!
     * \brief Destructor for FilterInfoGui.
     */
    virtual ~FilterInfoGui();
    /*!
     * \brief Sets the status message.
     * \param status The status message to display
     */
    virtual void setStatusMessage(const QString &status);
    /*!
     * \brief Sets the source location.
     * \param from The source location
     */
    virtual void setFrom(const QString &from);
    /*!
     * \brief Sets the destination location.
     * \param to The destination location
     */
    virtual void setTo(const QString &to);
    /*!
     * \brief Sets the current item description.
     * \param current The current item being processed
     */
    virtual void setCurrent(const QString &current);
    /*!
     * \brief Sets the current progress percentage.
     * \param percent The progress percentage (default 0)
     */
    virtual void setCurrent(int percent = 0);
    /*!
     * \brief Sets the overall progress percentage.
     * \param percent The overall progress percentage (default 0)
     */
    virtual void setOverall(int percent = 0);

    /*!
     * \brief Adds an informational log entry.
     * \param log The informational message to log
     */
    virtual void addInfoLogEntry(const QString &log);
    /*!
     * \brief Adds an error log entry.
     * \param log The error message to log
     */
    virtual void addErrorLogEntry(const QString &log);

    /*!
     * \brief Clears all logged entries.
     */
    virtual void clear();
    /*!
     * \brief Shows an alert dialog with the given message.
     * \param message The alert message
     */
    virtual void alert(const QString &message);
    /*!
     * \brief Returns the parent widget.
     * \return The parent widget
     */
    virtual QWidget *parent() const;
};
}

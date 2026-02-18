/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"

namespace MailImporter
{
/*!
 * \class MailImporter::MessageStatus
 * \inmodule MailImporter
 * \inheaderfile MailImporter/MessageStatus
 *
 * \brief The MessageStatus class.
 * \author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT MessageStatus
{
public:
    /*!
     * \brief Constructs a MessageStatus.
     */
    MessageStatus();
    /*!
     * \brief Destructor for MessageStatus.
     */
    ~MessageStatus();

    /*!
     * \brief Sets the read status of the message.
     * \param state True if the message is read
     */
    void setRead(bool state);
    /*!
     * \brief Returns whether the message is read.
     * \return True if the message is read
     */
    [[nodiscard]] bool isRead() const;

    /*!
     * \brief Sets the deleted status of the message.
     * \param state True if the message is deleted
     */
    void setDeleted(bool state);
    /*!
     * \brief Returns whether the message is deleted.
     * \return True if the message is deleted
     */
    [[nodiscard]] bool isDeleted() const;

    /*!
     * \brief Sets the replied status of the message.
     * \param state True if the message has been replied to
     */
    void setReplied(bool state);
    /*!
     * \brief Returns whether the message has been replied to.
     * \return True if the message has been replied to
     */
    [[nodiscard]] bool isReplied() const;

    /*!
     * \brief Sets the forwarded status of the message.
     * \param state True if the message has been forwarded
     */
    void setForwarded(bool state);
    /*!
     * \brief Returns whether the message has been forwarded.
     * \return True if the message has been forwarded
     */
    [[nodiscard]] bool isForwarded() const;

private:
    bool mRead = false;
    bool mDeleted = false;
    bool mReplied = false;
    bool mForwarded = false;
};
}

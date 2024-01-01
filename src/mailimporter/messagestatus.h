/*
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_export.h"

namespace MailImporter
{
/**
 * @brief The MessageStatus class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT MessageStatus
{
public:
    MessageStatus();
    ~MessageStatus();

    void setRead(bool state);
    [[nodiscard]] bool isRead() const;

    void setDeleted(bool state);
    [[nodiscard]] bool isDeleted() const;

    void setReplied(bool state);
    [[nodiscard]] bool isReplied() const;

    void setForwarded(bool state);
    [[nodiscard]] bool isForwarded() const;

private:
    bool mRead = false;
    bool mDeleted = false;
    bool mReplied = false;
    bool mForwarded = false;
};
}

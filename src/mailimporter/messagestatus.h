/*
  SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MESSAGESTATUS_H
#define MESSAGESTATUS_H

#include "mailimporter_export.h"
#include <QtGlobal>

namespace MailImporter {
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
    Q_REQUIRED_RESULT bool isRead() const;

    void setDeleted(bool state);
    Q_REQUIRED_RESULT bool isDeleted() const;

    void setReplied(bool state);
    Q_REQUIRED_RESULT bool isReplied() const;

    void setForwarded(bool state);
    Q_REQUIRED_RESULT bool isForwarded() const;
private:
    bool mRead = false;
    bool mDeleted = false;
    bool mReplied = false;
    bool mForwarded = false;
};
}
#endif // MESSAGESTATUS_H

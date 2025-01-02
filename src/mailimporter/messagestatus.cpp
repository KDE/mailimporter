/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "messagestatus.h"

using namespace MailImporter;

MessageStatus::MessageStatus()
{
}

MessageStatus::~MessageStatus()
{
}

void MessageStatus::setRead(bool state)
{
    mRead = state;
}

bool MessageStatus::isRead() const
{
    return mRead;
}

void MessageStatus::setDeleted(bool state)
{
    mDeleted = state;
}

bool MessageStatus::isDeleted() const
{
    return mDeleted;
}

void MessageStatus::setReplied(bool state)
{
    mReplied = state;
}

bool MessageStatus::isReplied() const
{
    return mReplied;
}

void MessageStatus::setForwarded(bool state)
{
    mForwarded = state;
}

bool MessageStatus::isForwarded() const
{
    return mForwarded;
}

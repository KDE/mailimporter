/*
  Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

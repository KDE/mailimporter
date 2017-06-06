/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MESSAGESTATUS_H
#define MESSAGESTATUS_H

#include "mailimporter_export.h"

namespace MailImporter {
class MAILIMPORTER_EXPORT MessageStatus
{
public:
    MessageStatus();
    ~MessageStatus();

    void setRead(bool state);
    bool isRead() const;

    void setDeleted(bool state);
    bool isDeleted() const;

    void setReplied(bool state);
    bool isReplied() const;

    void setForwarded(bool state);
    bool isForwarded() const;
private:
    bool mRead;
    bool mDeleted;
    bool mReplied;
    bool mForwarded;
};
}
#endif // MESSAGESTATUS_H

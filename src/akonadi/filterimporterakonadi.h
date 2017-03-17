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

#ifndef FILTERIMPORTERAKONADI_H
#define FILTERIMPORTERAKONADI_H

#include <MailImporter/FilterImporterBase>
#include <Akonadi/KMime/MessageStatus>
#include <AkonadiCore/Collection>
#include <KMime/Message>
#include "mailimporter_export.h"
#include <QString>

class MAILIMPORTER_EXPORT FilterImporterAkonadi : public MailImporter::FilterImporterBase
{
public:
    FilterImporterAkonadi(MailImporter::FilterInfo *info);
    ~FilterImporterAkonadi();

    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status) Q_DECL_OVERRIDE;
    void clear() Q_DECL_OVERRIDE;
private:
    static Akonadi::MessageStatus convertToAkonadiMessageStatus(const MailImporter::MessageStatus &status);
    Akonadi::Collection parseFolderString(const QString &folderParseString);
    bool checkForDuplicates(const QString &msgID,
                                    const Akonadi::Collection &msgCollection,
                                    const QString &messageFolder);
    Akonadi::Collection addSubCollection(const Akonadi::Collection &baseCollection,
            const QString &newCollectionPathName);
    bool addAkonadiMessage(const Akonadi::Collection &collection,
                                   const KMime::Message::Ptr &message, Akonadi::MessageStatus status);


    QMultiMap<QString, QString> mMessageFolderMessageIDMap;
    QMap<QString, Akonadi::Collection> mMessageFolderCollectionMap;
};

#endif // FILTERIMPORTERAKONADI_H

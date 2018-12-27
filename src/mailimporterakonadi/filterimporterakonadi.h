/*
  Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#ifndef FILTERIMPORTERAKONADI_H
#define FILTERIMPORTERAKONADI_H

#include <MailImporter/FilterImporterBase>
#include <Akonadi/KMime/MessageStatus>
#include <AkonadiCore/Collection>
#include <KMime/Message>
#include "mailimporterakonadi_export.h"
#include <QString>
namespace MailImporter {
class MAILIMPORTERAKONADI_EXPORT FilterImporterAkonadi : public MailImporter::FilterImporterBase
{
public:
    FilterImporterAkonadi(MailImporter::FilterInfo *info);
    ~FilterImporterAkonadi() override;

    bool importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status) override;
    void clear() override;
    void clearCountDuplicate() override;
    int countDuplicates() const override;
    static Akonadi::MessageStatus convertToAkonadiMessageStatus(const MailImporter::MessageStatus &status);

    Akonadi::Collection rootCollection() const;
    void setRootCollection(const Akonadi::Collection &collection);

    QString topLevelFolder() const override;
    bool importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone) override;

private:
    /**
    * Creates a hierachy of collections based on the given path string. The collection
    * hierachy will be placed under the root collection.
    * For example, if the folderParseString "foo/bar/test" is passsed to this method, it
    * will make sure the root collection has a subcollection named "foo", which in turn
    * has a subcollection named "bar", which again has a subcollection named "test".
    * The "test" collection will be returned.
    * An invalid collection will be returned in case of an error.
    */
    Akonadi::Collection parseFolderString(const QString &folderParseString);
    /**
    * Checks for duplicate messages in the collection by message ID.
    * returns true if a duplicate was detected.
    * NOTE: Only call this method if a message ID exists, otherwise
    * you could get false positives.
    */
    bool checkForDuplicates(const QString &msgID, const Akonadi::Collection &msgCollection, const QString &messageFolder);
    /**
    * Adds a single subcollection to the given base collection and returns it.
    * Use parseFolderString() instead if you want to create hierachies of collections.
    */
    Akonadi::Collection addSubCollection(const Akonadi::Collection &baseCollection, const QString &newCollectionPathName);
    bool addAkonadiMessage(const Akonadi::Collection &collection, const KMime::Message::Ptr &message, Akonadi::MessageStatus status);

    QMultiMap<QString, QString> mMessageFolderMessageIDMap;
    QMap<QString, Akonadi::Collection> mMessageFolderCollectionMap;
    Akonadi::Collection mRootCollection;
    int mCountDuplicates = 0;
};
}
#endif // FILTERIMPORTERAKONADI_H

/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporterakonadi_export.h"
#include <Akonadi/Collection>
#include <Akonadi/MessageStatus>
#include <KMime/Message>
#include <MailImporter/FilterImporterBase>
#include <QString>
namespace MailImporter
{
/**
 * @brief The FilterImporterAkonadi class
 * @author Laurent Montel <montel@kde.org>
 */
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
     * Creates a hierarchy of collections based on the given path string. The collection
     * hierarchy will be placed under the root collection.
     * For example, if the folderParseString "foo/bar/test" is passed to this method, it
     * will make sure the root collection has a subcollection named "foo", which in turn
     * has a subcollection named "bar", which again has a subcollection named "test".
     * The "test" collection will be returned.
     * An invalid collection will be returned in case of an error.
     */
    MAILIMPORTERAKONADI_NO_EXPORT Akonadi::Collection parseFolderString(const QString &folderParseString);
    /**
     * Checks for duplicate messages in the collection by message ID.
     * returns true if a duplicate was detected.
     * NOTE: Only call this method if a message ID exists, otherwise
     * you could get false positives.
     */
    MAILIMPORTERAKONADI_NO_EXPORT bool checkForDuplicates(const QString &msgID, const Akonadi::Collection &msgCollection, const QString &messageFolder);
    /**
     * Adds a single subcollection to the given base collection and returns it.
     * Use parseFolderString() instead if you want to create hierarchies of collections.
     */
    MAILIMPORTERAKONADI_NO_EXPORT Akonadi::Collection addSubCollection(const Akonadi::Collection &baseCollection, const QString &newCollectionPathName);
    MAILIMPORTERAKONADI_NO_EXPORT bool
    addAkonadiMessage(const Akonadi::Collection &collection, const KMime::Message::Ptr &message, Akonadi::MessageStatus status);

    QMultiMap<QString, QString> mMessageFolderMessageIDMap;
    QMap<QString, Akonadi::Collection> mMessageFolderCollectionMap;
    Akonadi::Collection mRootCollection;
    int mCountDuplicates = 0;
};
}

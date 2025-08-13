/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterimporterakonadi.h"
using namespace Qt::Literals::StringLiterals;

#include "mailimporterakonadi_debug.h"
#include <Akonadi/CollectionCreateJob>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/MessageFlags>
#include <Akonadi/MessageParts>
#include <KLocalizedString>
#include <MailImporter/FilterInfo>
#include <QFile>
#include <QScopedPointer>
#include <QUrl>

using namespace MailImporter;

FilterImporterAkonadi::FilterImporterAkonadi(MailImporter::FilterInfo *info)
    : MailImporter::FilterImporterBase(info)
{
}

FilterImporterAkonadi::~FilterImporterAkonadi()
{
}

void FilterImporterAkonadi::clear()
{
    mMessageFolderMessageIDMap.clear();
    mMessageFolderCollectionMap.clear();
    mCountDuplicates = 0;
}

Akonadi::MessageStatus FilterImporterAkonadi::convertToAkonadiMessageStatus(const MailImporter::MessageStatus &status)
{
    Akonadi::MessageStatus akonadiStatus;
    if (status.isDeleted()) {
        akonadiStatus.setDeleted(true);
    }
    if (status.isRead()) {
        akonadiStatus.setRead(true);
    }
    if (status.isForwarded()) {
        akonadiStatus.setForwarded(true);
    }
    if (status.isReplied()) {
        akonadiStatus.setReplied(true);
    }
    return akonadiStatus;
}

Akonadi::Collection FilterImporterAkonadi::rootCollection() const
{
    return mRootCollection;
}

void FilterImporterAkonadi::setRootCollection(const Akonadi::Collection &collection)
{
    mRootCollection = collection;
}

QString FilterImporterAkonadi::topLevelFolder() const
{
    return mRootCollection.name();
}

bool FilterImporterAkonadi::importMessage(const QString &folderName,
                                          const QString &msgPath,
                                          bool duplicateCheck,
                                          const MailImporter::MessageStatus &mailImporterstatus)
{
    const Akonadi::MessageStatus status = convertToAkonadiMessageStatus(mailImporterstatus);
    // Create the mail folder (if not already created).
    Akonadi::Collection mailFolder = parseFolderString(folderName);
    QUrl msgUrl = QUrl::fromLocalFile(msgPath);
    if (!msgUrl.isEmpty() && msgUrl.isLocalFile()) {
        QFile f(msgUrl.toLocalFile());
        QByteArray msgText;
        if (f.open(QIODevice::ReadOnly)) {
            msgText = f.readAll();
            f.close();
        } else {
            qCWarning(MAILIMPORTERAKONADI_LOG) << "Failed to read temporary file: " << f.errorString();
        }
        if (msgText.isEmpty()) {
            mInfo->addErrorLogEntry(i18n("Error: failed to read temporary file at %1", msgPath));
            return false;
        }

        // Construct a message.
        KMime::Message::Ptr newMessage(new KMime::Message());
        newMessage->setContent(msgText);
        newMessage->parse();

        if (duplicateCheck) {
            // Get the messageID.
            const KMime::Headers::Base *messageIDHeader = newMessage->messageID(false);
            QString messageID;
            if (messageIDHeader) {
                messageID = messageIDHeader->asUnicodeString();
            }

            if (!messageID.isEmpty()) {
                // Check for duplicate.
                if (checkForDuplicates(messageID, mailFolder, folderName)) {
                    mCountDuplicates++;
                    return false;
                }
            }
        }

        // Add it to the collection.
        if (mailFolder.isValid()) {
            addAkonadiMessage(mailFolder, newMessage, status);
        } else {
            mInfo->alert(i18n("<b>Warning:</b> Got a bad message folder, adding to root folder."));
            addAkonadiMessage(rootCollection(), newMessage, status);
        }
    } else {
        qCWarning(MAILIMPORTERAKONADI_LOG) << "Url is not temporary file: " << msgUrl;
    }
    return true;
}

Akonadi::Collection FilterImporterAkonadi::parseFolderString(const QString &folderParseString)
{
    // Return an already created collection:
    const Akonadi::Collection col = mMessageFolderCollectionMap.value(folderParseString);
    if (col.isValid()) {
        return col;
    }

    // The folder hasn't yet been created, create it now.
    const QStringList folderList = folderParseString.split(u'/', Qt::SkipEmptyParts);
    bool isFirst = true;
    QString folderBuilder;
    Akonadi::Collection lastCollection;

    // Create each folder on the folder list and add it the map.
    for (const QString &folder : folderList) {
        if (isFirst) {
            mMessageFolderCollectionMap[folder] = addSubCollection(rootCollection(), folder);
            folderBuilder = folder;
            lastCollection = mMessageFolderCollectionMap[folder];
            isFirst = false;
        } else {
            folderBuilder += u'/' + folder;
            mMessageFolderCollectionMap[folderBuilder] = addSubCollection(lastCollection, folder);
            lastCollection = mMessageFolderCollectionMap[folderBuilder];
        }
    }

    return lastCollection;
}

Akonadi::Collection FilterImporterAkonadi::addSubCollection(const Akonadi::Collection &baseCollection, const QString &newCollectionPathName)
{
    // Ensure that the collection doesn't already exist, if it does just return it.
    auto fetchJob = new Akonadi::CollectionFetchJob(baseCollection, Akonadi::CollectionFetchJob::FirstLevel);
    if (!fetchJob->exec()) {
        mInfo->alert(i18n("<b>Warning:</b> Could not check that the folder already exists. Reason: %1", fetchJob->errorString()));
        return Akonadi::Collection();
    }
    const Akonadi::Collection::List lstCols = fetchJob->collections();
    for (const Akonadi::Collection &subCollection : lstCols) {
        if (subCollection.name() == newCollectionPathName) {
            return subCollection;
        }
    }

    // The subCollection doesn't exist, create a new one
    Akonadi::Collection newSubCollection;
    newSubCollection.setParentCollection(baseCollection);
    newSubCollection.setName(newCollectionPathName);

    auto job = new Akonadi::CollectionCreateJob(newSubCollection);
    if (!job->exec()) {
        mInfo->alert(i18n("<b>Error:</b> Could not create folder. Reason: %1", job->errorString()));
        return Akonadi::Collection();
    }
    // Return the newly created collection
    Akonadi::Collection collection = job->collection();
    return collection;
}

bool FilterImporterAkonadi::checkForDuplicates(const QString &msgID, const Akonadi::Collection &msgCollection, const QString &messageFolder)
{
    bool folderFound = false;

    // Check if the contents of this collection have already been found.
    QMultiMap<QString, QString>::const_iterator end(mMessageFolderMessageIDMap.constEnd());
    for (QMultiMap<QString, QString>::const_iterator it = mMessageFolderMessageIDMap.constBegin(); it != end; ++it) {
        if (it.key() == messageFolder) {
            folderFound = true;
            break;
        }
    }

    if (!folderFound) {
        // Populate the map with message IDs that are in that collection.
        if (msgCollection.isValid()) {
            Akonadi::ItemFetchJob job(msgCollection);
            job.fetchScope().fetchPayloadPart(Akonadi::MessagePart::Header);
            if (!job.exec()) {
                mInfo->addInfoLogEntry(
                    i18n("<b>Warning:</b> Could not fetch mail in folder %1. Reason: %2"
                         " You may have duplicate messages.",
                         messageFolder,
                         job.errorString()));
            } else {
                const Akonadi::Item::List items = job.items();
                for (const Akonadi::Item &messageItem : items) {
                    if (!messageItem.isValid()) {
                        mInfo->addInfoLogEntry(i18n("<b>Warning:</b> Got an invalid message in folder %1.", messageFolder));
                    } else {
                        if (!messageItem.hasPayload<KMime::Message::Ptr>()) {
                            continue;
                        }
                        const auto message = messageItem.payload<KMime::Message::Ptr>();
                        const KMime::Headers::Base *messageID = message->messageID(false);
                        if (messageID) {
                            if (!messageID->isEmpty()) {
                                mMessageFolderMessageIDMap.insert(messageFolder, messageID->asUnicodeString());
                            }
                        }
                    }
                }
            }
        }
    }

    // Check if this message has a duplicate
    QMultiMap<QString, QString>::const_iterator endMsgID(mMessageFolderMessageIDMap.constEnd());
    for (QMultiMap<QString, QString>::const_iterator it = mMessageFolderMessageIDMap.constBegin(); it != endMsgID; ++it) {
        if (it.key() == messageFolder && it.value() == msgID) {
            return true;
        }
    }

    // The message isn't a duplicate, but add it to the map for checking in the future.
    mMessageFolderMessageIDMap.insert(messageFolder, msgID);
    return false;
}

bool FilterImporterAkonadi::addAkonadiMessage(const Akonadi::Collection &collection, const KMime::Message::Ptr &message, Akonadi::MessageStatus status)
{
    Akonadi::Item item;

    item.setMimeType(u"message/rfc822"_s);

    if (status.isOfUnknownStatus()) {
        KMime::Headers::Base *statusHeaders = message->headerByType("X-Status");
        if (statusHeaders) {
            if (!statusHeaders->isEmpty()) {
                status.setStatusFromStr(statusHeaders->asUnicodeString());
                item.setFlags(status.statusFlags());
            }
        }
    } else {
        item.setFlags(status.statusFlags());
    }

    Akonadi::MessageFlags::copyMessageFlags(*message, item);
    item.setPayload<KMime::Message::Ptr>(message);
    QScopedPointer<Akonadi::ItemCreateJob> job(new Akonadi::ItemCreateJob(item, collection));
    job->setAutoDelete(false);
    if (!job->exec()) {
        mInfo->alert(i18n("<b>Error:</b> Could not add message to folder %1. Reason: %2", collection.name(), job->errorString()));
        return false;
    }
    return true;
}

void FilterImporterAkonadi::clearCountDuplicate()
{
    mCountDuplicates = 0;
}

int FilterImporterAkonadi::countDuplicates() const
{
    return mCountDuplicates;
}

bool FilterImporterAkonadi::importMessage(const KArchiveFile *file, const QString &folderPath, int &nbTotal, int &fileDone)
{
    const Akonadi::Collection collection = parseFolderString(folderPath);
    if (!collection.isValid()) {
        mInfo->addErrorLogEntry(i18n("Unable to retrieve folder for folder path %1.", folderPath));
        return false;
    }

    KMime::Message::Ptr newMessage(new KMime::Message());
    newMessage->setContent(file->data());
    newMessage->parse();

    if (mInfo->removeDupMessage()) {
        KMime::Headers::MessageID *messageId = newMessage->messageID(false);
        if (messageId) {
            const QString messageIdStr = messageId->asUnicodeString();
            if (!messageIdStr.isEmpty()) {
                if (checkForDuplicates(messageIdStr, collection, folderPath)) {
                    nbTotal--;
                    return true;
                }
            }
        }
    }

    const bool result = addAkonadiMessage(collection, newMessage, Akonadi::MessageStatus());
    if (result) {
        fileDone++;
    }
    return result;
}

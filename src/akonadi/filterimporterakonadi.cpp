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

#include "filterimporterakonadi.h"
#include "mailimporter_debug.h"
#include <AkonadiCore/Collection>
#include <KMime/Message>

FilterImporterAkonadi::FilterImporterAkonadi(MailImporter::FilterInfo *info)
    : MailImporter::FilterImporterBase(info)
{

}

FilterImporterAkonadi::~FilterImporterAkonadi()
{

}

Akonadi::MessageStatus FilterImporterAkonadi::convertToAkonadiMessageStatus(const MailImporter::MessageStatus &status)
{

    //TODO
    return Akonadi::MessageStatus();
}

bool FilterImporterAkonadi::importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status)
{
#if 0
    QString messageID;
    // Create the mail folder (if not already created).
    Akonadi::Collection mailFolder = parseFolderString(folderName);
    QUrl msgUrl = QUrl::fromLocalFile(msgPath);
    if (!msgUrl.isEmpty() && msgUrl.isLocalFile()) {

        QFile f(msgUrl.toLocalFile());
        QByteArray msgText;
        if (!f.open(QIODevice::ReadOnly)) {
            qCWarning(MAILIMPORTER_LOG) << "Failed to read temporary file: " << f.errorString();
        } else {
            msgText = f.readAll();
            f.close();
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
            if (messageIDHeader) {
                messageID = messageIDHeader->asUnicodeString();
            }

            if (!messageID.isEmpty()) {
                // Check for duplicate.
                if (checkForDuplicates(messageID, mailFolder, folderName)) {
                    d->count_duplicates++;
                    return false;
                }
            }
        }

        // Add it to the collection.
        if (mailFolder.isValid()) {
            addAkonadiMessage(mailFolder, newMessage, status);
        } else {
            mInfo->alert(i18n("<b>Warning:</b> Got a bad message folder, adding to root folder."));
            addAkonadiMessage(d->filterInfo->rootCollection(), newMessage, status);
        }
    } else {
        qCWarning(MAILIMPORTER_LOG) << "Url is not temporary file: " << msgUrl;
    }
    return true;
#else
    return false;
#endif
}
#if 0
Akonadi::Collection Filter::parseFolderString(const QString &folderParseString)
{
    // Return an already created collection:
    const Akonadi::Collection col = d->messageFolderCollectionMap.value(folderParseString);
    if (col.isValid()) {
        return col;
    }

    // The folder hasn't yet been created, create it now.
    const QStringList folderList = folderParseString.split(QLatin1Char('/'), QString::SkipEmptyParts);
    bool isFirst = true;
    QString folderBuilder;
    Akonadi::Collection lastCollection;

    // Create each folder on the folder list and add it the map.
    for (const QString &folder : folderList) {
        if (isFirst) {
            d->messageFolderCollectionMap[folder] = addSubCollection(d->filterInfo->rootCollection(), folder);
            folderBuilder = folder;
            lastCollection = d->messageFolderCollectionMap[folder];
            isFirst = false;
        } else {
            folderBuilder += QLatin1Char('/') + folder;
            d->messageFolderCollectionMap[folderBuilder] = addSubCollection(lastCollection, folder);
            lastCollection = d->messageFolderCollectionMap[folderBuilder];
        }
    }

    return lastCollection;
}

Akonadi::Collection Filter::addSubCollection(const Akonadi::Collection &baseCollection,
        const QString &newCollectionPathName)
{
    // Ensure that the collection doesn't already exsit, if it does just return it.
    Akonadi::CollectionFetchJob *fetchJob = new Akonadi::CollectionFetchJob(baseCollection,
            Akonadi::CollectionFetchJob::FirstLevel);
    if (!fetchJob->exec()) {
        d->filterInfo->alert(i18n("<b>Warning:</b> Could not check that the folder already exists. Reason: %1",
                                  fetchJob->errorString()));
        return Akonadi::Collection();
    }
    const Akonadi::Collection::List lstCols = fetchJob->collections();
    for (const Akonadi::Collection &subCollection : lstCols) {
        if (subCollection.name() == newCollectionPathName) {
            return subCollection;
        }
    }

    // The subCollection doesn't exsit, create a new one
    Akonadi::Collection newSubCollection;
    newSubCollection.setParentCollection(baseCollection);
    newSubCollection.setName(newCollectionPathName);

    QScopedPointer<Akonadi::CollectionCreateJob> job(new Akonadi::CollectionCreateJob(newSubCollection));
    job->setAutoDelete(false);
    if (!job->exec()) {
        d->filterInfo->alert(i18n("<b>Error:</b> Could not create folder. Reason: %1",
                                  job->errorString()));
        return Akonadi::Collection();
    }
    // Return the newly created collection
    Akonadi::Collection collection = job->collection();
    return collection;
}

bool Filter::checkForDuplicates(const QString &msgID,
                                const Akonadi::Collection &msgCollection,
                                const QString &messageFolder)
{
    bool folderFound = false;

    // Check if the contents of this collection have already been found.
    QMultiMap<QString, QString>::const_iterator end(d->messageFolderMessageIDMap.constEnd());
    for (QMultiMap<QString, QString>::const_iterator it = d->messageFolderMessageIDMap.constBegin(); it != end; ++it) {
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
                d->filterInfo->addInfoLogEntry(i18n("<b>Warning:</b> Could not fetch mail in folder %1. Reason: %2"
                                                    " You may have duplicate messages.", messageFolder, job.errorString()));
            } else {
                const Akonadi::Item::List items = job.items();
                for (const Akonadi::Item &messageItem : items) {
                    if (!messageItem.isValid()) {
                        d->filterInfo->addInfoLogEntry(i18n("<b>Warning:</b> Got an invalid message in folder %1.", messageFolder));
                    } else {
                        if (!messageItem.hasPayload<KMime::Message::Ptr>()) {
                            continue;
                        }
                        const KMime::Message::Ptr message = messageItem.payload<KMime::Message::Ptr>();
                        const KMime::Headers::Base *messageID = message->messageID(false);
                        if (messageID) {
                            if (!messageID->isEmpty()) {
                                d->messageFolderMessageIDMap.insert(messageFolder, messageID->asUnicodeString());
                            }
                        }
                    }
                }
            }
        }
    }

    // Check if this message has a duplicate
    QMultiMap<QString, QString>::const_iterator endMsgID(d->messageFolderMessageIDMap.constEnd());
    for (QMultiMap<QString, QString>::const_iterator it = d->messageFolderMessageIDMap.constBegin(); it != endMsgID; ++it) {
        if (it.key() == messageFolder &&
                it.value() == msgID) {
            return true;
        }
    }

    // The message isn't a duplicate, but add it to the map for checking in the future.
    d->messageFolderMessageIDMap.insert(messageFolder, msgID);
    return false;
}

#endif

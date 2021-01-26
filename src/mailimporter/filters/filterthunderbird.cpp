/*
  filterthunderbird.cpp  -  Thunderbird mail import

  SPDX-FileCopyrightText: 2005 Danny Kukawka <danny.kukawka@web.de>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterthunderbird.h"
#include "selectthunderbirdprofilewidget.h"
#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <QFile>
#include <QFileDialog>
#include <QPointer>
#include <QRegularExpression>
#include <QTemporaryFile>

using namespace MailImporter;

/** Default constructor. */
FilterThunderbird::FilterThunderbird()
    : Filter(i18n("Import Thunderbird/Mozilla Local Mails and Folder Structure"),
             QStringLiteral("Danny Kukawka"),
             i18n("<p><b>Thunderbird/Mozilla import filter</b></p>"
                  "<p>Select your base Thunderbird/Mozilla mailfolder"
                  " (usually ~/.thunderbird/*.default/Mail/Local Folders/).</p>"
                  "<p><b>Note:</b> Never choose a Folder which <u>does not</u> contain mbox-files (for example,"
                  " a maildir): if you do, you will get many new folders.</p>"
                  "<p>Since it is possible to recreate the folder structure, the folders "
                  "will be stored under: \"Thunderbird-Import\".</p>"))
{
}

/** Destructor. */
FilterThunderbird::~FilterThunderbird()
{
}

QString FilterThunderbird::isMailerFound()
{
    QDir directory(FilterThunderbird::defaultSettingsPath());
    if (directory.exists()) {
        QString currentProfile;
        const QMap<QString, QString> listOfPath = FilterThunderbird::listProfile(currentProfile, FilterThunderbird::defaultSettingsPath());
        bool foundMailConfigurated = false;
        QMap<QString, QString>::const_iterator i = listOfPath.constBegin();
        while (i != listOfPath.constEnd()) {
            QDir dir(FilterThunderbird::defaultSettingsPath() + QLatin1Char('/') + i.value());
            if (!dir.entryList(QStringList({QStringLiteral("ImapMail"), QStringLiteral("Mail")}), QDir::Dirs).isEmpty()) {
                foundMailConfigurated = true;
                break;
            }
            ++i;
        }
        if (foundMailConfigurated) {
            return i18nc("name of thunderbird application", "Thunderbird");
        } else {
            return {};
        }
    }
    return {};
}

QString FilterThunderbird::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1String("/.thunderbird/");
}

QString FilterThunderbird::defaultProfile(const QString &defaultSettingPath, QWidget *parent)
{
    QString currentProfile;
    QMap<QString, QString> listProfile = FilterThunderbird::listProfile(currentProfile, defaultSettingPath);
    if (listProfile.isEmpty()) {
        return QString();
    } else if (listProfile.count() == 1) {
        return currentProfile;
    } else {
        QPointer<SelectThunderbirdProfileDialog> dialog = new SelectThunderbirdProfileDialog(parent);
        dialog->fillProfile(listProfile, currentProfile);
        if (dialog->exec()) {
            currentProfile = dialog->selectedProfile();
            delete dialog;
            return currentProfile;
        }
        delete dialog;
    }
    return currentProfile;
}

QMap<QString, QString> FilterThunderbird::listProfile(QString &currentProfile, const QString &defaultSettingPath)
{
    const QString thunderbirdPath = defaultSettingPath + QLatin1String("/profiles.ini");
    QMap<QString, QString> lstProfile;
    QFile profiles(thunderbirdPath);
    if (profiles.exists()) {
        // ini file.
        KConfig config(thunderbirdPath);
        const QStringList profileList = config.groupList().filter(QRegularExpression(QStringLiteral("Profile\\d+")));
        const bool uniqProfile = (profileList.count() == 1);
        if (uniqProfile) {
            KConfigGroup group = config.group(profileList.at(0));
            const QString path = group.readEntry("Path");
            const QString name = group.readEntry(QStringLiteral("Name"));
            currentProfile = path;
            lstProfile.insert(name, path);
            return lstProfile;
        } else {
            for (const QString &profileName : profileList) {
                KConfigGroup group = config.group(profileName);
                const QString path = group.readEntry("Path");
                const QString name = group.readEntry(QStringLiteral("Name"));
                if (group.hasKey("Default") && (group.readEntry("Default", 0) == 1)) {
                    currentProfile = path;
                }
                lstProfile.insert(name, path);
            }
        }
    }
    return lstProfile;
}

QString FilterThunderbird::defaultInstallFolder() const
{
    return QStringLiteral("Thunderbird-Import/");
}

QString FilterThunderbird::settingsPath()
{
    return FilterThunderbird::defaultSettingsPath();
}

void FilterThunderbird::import()
{
    /**
     * We ask the user to choose Thunderbird's root directory.
     * This should be usually ~/.thunderbird/xxxx.default/Mail/Local Folders/
     */
    QString thunderDir = settingsPath();
    QDir d(thunderDir);
    if (!d.exists()) {
        thunderDir = QDir::homePath();
    }
    // Select directory from where I have to import files
    const QString maildir = QFileDialog::getExistingDirectory(nullptr, QString(), thunderDir);
    if (!maildir.isEmpty()) {
        const QString mailDirThunderbird = maildir + QLatin1String("/Mail/Local Folders/");
        if (QDir(mailDirThunderbird).exists()) {
            importMails(mailDirThunderbird);
        } else {
            importMails(maildir);
        }
    }
}

bool FilterThunderbird::excludeFiles(const QString &file)
{
    if ((file.endsWith(QLatin1String(".msf")) || file.endsWith(QLatin1String(".dat")) || file.endsWith(QLatin1String(".json"))
         || file.endsWith(QLatin1String(".html")))) {
        return true;
    }
    return false;
}

void FilterThunderbird::importMails(const QString &maildir)
{
    if (maildir.isEmpty()) {
        filterInfo()->alert(i18n("No directory selected."));
        return;
    }
    setMailDir(maildir);
    /**
     * If the user only select homedir no import needed because
     * there should be no files and we surely import wrong files.
     */
    if (mailDir() == QDir::homePath() || mailDir() == (QDir::homePath() + QLatin1Char('/'))) {
        filterInfo()->addErrorLogEntry(i18n("No files found for import."));
    } else {
        filterInfo()->setOverall(0);
        /** Recursive import of the MailArchives */
        QDir dir(mailDir());
        const QStringList rootSubDirs = dir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name); // Removal of . and ..
        int currentDir = 1, numSubDirs = rootSubDirs.size();
        QStringList::ConstIterator end = rootSubDirs.constEnd();
        for (QStringList::ConstIterator filename = rootSubDirs.constBegin(); filename != end; ++filename, ++currentDir) {
            if (filterInfo()->shouldTerminate()) {
                break;
            }
            importDirContents(dir.filePath(*filename), *filename, *filename);
            filterInfo()->setOverall((int)((float)currentDir / numSubDirs * 100));
        }

        /** import last but not least all archives from the root-dir */
        QDir importDir(mailDir());
        const QStringList files = importDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Files, QDir::Name);
        QStringList::ConstIterator mailFileEnd = files.constEnd();
        for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != mailFileEnd; ++mailFile) {
            if (filterInfo()->shouldTerminate()) {
                break;
            }
            QString temp_mailfile = *mailFile;
            if (!excludeFiles(temp_mailfile)) {
                filterInfo()->addInfoLogEntry(i18n("Start import file %1...", temp_mailfile));
                importMBox(mailDir() + temp_mailfile, temp_mailfile, QString());
            }
        }

        filterInfo()->addInfoLogEntry(i18n("Finished importing emails from %1", mailDir()));
        if (countDuplicates() > 0) {
            filterInfo()->addInfoLogEntry(i18np("1 duplicate message not imported", "%1 duplicate messages not imported", countDuplicates()));
        }
    }
    if (filterInfo()->shouldTerminate()) {
        filterInfo()->addInfoLogEntry(i18n("Finished import, canceled by user."));
    }
    filterInfo()->setCurrent(100);
    filterInfo()->setOverall(100);
}

/**
 * Import of a directory contents.
 * @param info Information storage for the operation.
 * @param dirName The name of the directory to import.
 * @param KMailRootDir The directory's root directory in KMail's folder structure.
 * @param KMailSubDir The directory's direct ancestor in KMail's folder structure.
 */
void FilterThunderbird::importDirContents(const QString &dirName, const QString &KMailRootDir, const QString &KMailSubDir)
{
    if (filterInfo()->shouldTerminate()) {
        return;
    }
    /** Here Import all archives in the current dir */
    QDir importDir(dirName);
    const QStringList files = importDir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Files, QDir::Name);
    QStringList::ConstIterator mailFileEnd = files.constEnd();
    for (QStringList::ConstIterator mailFile = files.constBegin(); mailFile != mailFileEnd; ++mailFile) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        QString temp_mailfile = *mailFile;
        if (!excludeFiles(temp_mailfile)) {
            filterInfo()->addInfoLogEntry(i18n("Start import file %1...", temp_mailfile));
            importMBox((dirName + QLatin1Char('/') + temp_mailfile), KMailRootDir, KMailSubDir);
        }
    }

    /** If there are subfolders, we import them one by one */
    QDir subfolders(dirName);
    const QStringList subDirs = subfolders.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name);
    QStringList::ConstIterator end = subDirs.constEnd();
    for (QStringList::ConstIterator filename = subDirs.constBegin(); filename != end; ++filename) {
        if (filterInfo()->shouldTerminate()) {
            break;
        }
        QString kSubDir;
        if (!KMailSubDir.isNull()) {
            kSubDir = KMailSubDir + QLatin1Char('/') + *filename;
        } else {
            kSubDir = *filename;
        }
        importDirContents(subfolders.filePath(*filename), KMailRootDir, kSubDir);
    }
}

/**
 * Import of a MBox file.
 * @param info Information storage for the operation.
 * @param dirName The MBox's name.
 * @param KMailRootDir The directory's root directory in KMail's folder structure.
 * @param KMailSubDir The directory's equivalent in KMail's folder structure. *
 */
void FilterThunderbird::importMBox(const QString &mboxName, const QString &rootDir, const QString &targetDir)
{
    QFile mbox(mboxName);
    if (!mbox.open(QIODevice::ReadOnly)) {
        filterInfo()->alert(i18n("Unable to open %1, skipping", mboxName));
    } else {
        bool first_msg = true;
        QFileInfo filenameInfo(mboxName);

        filterInfo()->setCurrent(0);
        if (mboxName.length() > 20) {
            QString tmp_info = mboxName;
            tmp_info.replace(mailDir(), QStringLiteral("../"));
            if (tmp_info.contains(QLatin1String(".sbd"))) {
                tmp_info.remove(QStringLiteral(".sbd"));
            }
            filterInfo()->setFrom(tmp_info);
        } else {
            filterInfo()->setFrom(mboxName);
        }
        if (targetDir.contains(QLatin1String(".sbd"))) {
            QString tmp_info = targetDir;
            tmp_info.remove(QStringLiteral(".sbd"));
            filterInfo()->setTo(tmp_info);
        } else {
            filterInfo()->setTo(targetDir);
        }

        QByteArray input(MAX_LINE, '\0');
        long l = 0;

        while (!mbox.atEnd()) {
            QTemporaryFile tmp;
            tmp.open();
            /** @todo check if the file is really a mbox, maybe search for 'from' string at start */
            /* comment by Danny:
             * Don't use QTextStream to read from mbox, better use QDataStream. QTextStream only
             * support Unicode/Latin1/Locale. So you lost information from emails with
             * charset!=Unicode/Latin1/Locale (e.g. KOI8-R) and Content-Transfer-Encoding != base64
             * (e.g. 8Bit). It also not help to convert the QTextStream to Unicode. By this you
             * get Unicode/UTF-email but KMail can't detect the correct charset.
             */
            QByteArray separate;

            if (!first_msg) {
                tmp.write(input.constData(), l);
            }
            l = mbox.readLine(input.data(), MAX_LINE); // read the first line, prevent "From "
            tmp.write(input.constData(), l);

            while (!mbox.atEnd() && (l = mbox.readLine(input.data(), MAX_LINE)) && ((separate = input.data()).left(5) != "From ")) {
                tmp.write(input.constData(), l);
            }
            tmp.flush();
            first_msg = false;

            QString destFolder;
            QString _targetDir = targetDir;
            if (!targetDir.isNull()) {
                if (_targetDir.contains(QLatin1String(".sbd"))) {
                    _targetDir.remove(QStringLiteral(".sbd"));
                }
                destFolder += defaultInstallFolder() + _targetDir + QLatin1Char('/') + filenameInfo.completeBaseName(); // mboxName;
            } else {
                destFolder = defaultInstallFolder() + rootDir;
                if (destFolder.contains(QLatin1String(".sbd"))) {
                    destFolder.remove(QStringLiteral(".sbd"));
                }
            }
            if (!importMessage(destFolder, tmp.fileName(), filterInfo()->removeDupMessage())) {
                filterInfo()->addErrorLogEntry(i18n("Could not import %1", tmp.fileName()));
            }

            int currentPercentage = (int)(((float)mbox.pos() / filenameInfo.size()) * 100);
            filterInfo()->setCurrent(currentPercentage);
            if (filterInfo()->shouldTerminate()) {
                mbox.close();
                return;
            }
        }
        mbox.close();
    }
}

/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "othermailerutil.h"
#include <KLocalizedString>
#include <QStandardPaths>
#include <QDir>

using namespace MailImporter;
QStringList OtherMailerUtil::isMailerFound()
{
    QStringList lst;
    QDir directory(OtherMailerUtil::trojitaDefaultPath());
    if (directory.exists()) {
        lst << i18nc("name of trojira application", "Trojita");
    }
    directory = OtherMailerUtil::gearyDefaultPath();
    if (directory.exists()) {
        lst << i18nc("name of geary application", "Geary");
    }
    directory = OtherMailerUtil::nylasMailDefaultPath();
    if (directory.exists()) {
        lst << i18nc("name of geary application", "Geary");
    }
    return lst;
}

QString OtherMailerUtil::trojitaDefaultPath()
{
    const QString path = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QLatin1String("/flaska.net/");
    return path;
}

QString OtherMailerUtil::gearyDefaultPath()
{
    const QString path = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QLatin1String("/geary/");
    return path;
}

QString OtherMailerUtil::nylasMailDefaultPath()
{
    const QString path = QDir::homePath() + QLatin1String("/.nylas-mail/");
    return path;
}

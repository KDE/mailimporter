/*
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterseamonkey.h"
#include <KLocalizedString>
using namespace MailImporter;

FilterSeaMonkey::FilterSeaMonkey()
    : FilterThunderbird()
{
    setName(i18n("Import SeaMonkey Mails and Folder Structure"));
    setAuthor(QStringLiteral("Laurent Montel"));
    setInfo(
        i18n("<p><b>SeaMonkey import filter</b></p>"
             "<p>Select your base SeaMonkey mailfolder"
             " (usually ~/.icedove/*.default/Mail/Local Folders/).</p>"
             "<p><b>Note:</b> Never choose a Folder which <u>does not</u> contain mbox-files (for example,"
             " a maildir): if you do, you will get many new folders.</p>"
             "<p>Since it is possible to recreate the folder structure, the folders "
             "will be stored under: \"SeaMonkey-Import\".</p>"));
}

FilterSeaMonkey::~FilterSeaMonkey()
{
}

QString FilterSeaMonkey::settingsPath()
{
    return FilterSeaMonkey::defaultSettingsPath();
}

QString FilterSeaMonkey::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1String("/.mozilla/seamonkey");
}

QString FilterSeaMonkey::defaultInstallFolder() const
{
    return QStringLiteral("SeaMonkey-Import/");
}

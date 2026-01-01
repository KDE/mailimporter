/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filtericedove.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
using namespace MailImporter;

FilterIcedove::FilterIcedove()
    : FilterThunderbird()
{
    setName(i18n("Import Icedove Mails and Folder Structure"));
    setAuthor(u"Laurent Montel"_s);
    setInfo(
        i18n("<p><b>Icedove import filter</b></p>"
             "<p>Select your base Icedove mailfolder"
             " (usually ~/.icedove/*.default/Mail/Local Folders/).</p>"
             "<p><b>Note:</b> Never choose a Folder which <u>does not</u> contain mbox-files (for example,"
             " a maildir): if you do, you will get many new folders.</p>"
             "<p>Since it is possible to recreate the folder structure, the folders "
             "will be stored under: \"Icedove-Import\".</p>"));
}

FilterIcedove::~FilterIcedove()
{
}

QString FilterIcedove::isMailerFound()
{
    QDir directory(FilterIcedove::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of icedove application", "Icedove");
    }
    return {};
}

QString FilterIcedove::settingsPath()
{
    return FilterIcedove::defaultSettingsPath();
}

QString FilterIcedove::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/.icedove/");
}

QString FilterIcedove::defaultInstallFolder() const
{
    return u"Icedove-Import/"_s;
}

/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

/* based on filter_sylpheed filter */

#include "filterclawsmail.h"
using namespace Qt::Literals::StringLiterals;

#include "mailimporter_debug.h"
#include <KLocalizedString>
#include <QDomDocument>
#include <QDomElement>

using namespace MailImporter;

/** Default constructor. */
FilterClawsMail::FilterClawsMail()
    : FilterSylpheed()
{
    setName(i18n("Import Claws-mail Maildirs and Folder Structure"));
    setAuthor(u"Laurent Montel"_s);
    setInfo(
        i18n("<p><b>Claws-mail import filter</b></p>"
             "<p>Select the base directory of the Claws-mail mailfolder you want to import "
             "(usually: ~/Mail ).</p>"
             "<p>Since it is possible to recreate the folder structure, the folders "
             "will be stored under: \"ClawsMail-Import\" in your local folder.</p>"
             "<p>This filter also recreates the status of message, e.g. new or forwarded.</p>"));
}

/** Destructor. */
FilterClawsMail::~FilterClawsMail()
{
}

QString FilterClawsMail::isMailerFound()
{
    QDir directory(FilterClawsMail::defaultSettingsPath());
    if (directory.exists()) {
        return i18nc("name of clawsMail application", "ClawsMail");
    }
    return {};
}

QString FilterClawsMail::defaultSettingsPath()
{
    return QDir::homePath() + QLatin1StringView("/.claws-mail/");
}

QString FilterClawsMail::localMailDirPath()
{
    QFile folderListFile(FilterClawsMail::defaultSettingsPath() + QLatin1StringView("/folderlist.xml"));
    if (folderListFile.exists()) {
        QDomDocument doc;
        if (!folderListFile.open(QIODevice::ReadOnly)) {
            qCWarning(MAILIMPORTER_LOG) << "Impossible to open " << folderListFile.fileName();
        }
        const QDomDocument::ParseResult parseResult = doc.setContent(&folderListFile);
        if (!parseResult) {
            qCDebug(MAILIMPORTER_LOG) << "Unable to load document.Parse error in line " << parseResult.errorLine << ", col " << parseResult.errorColumn << ": "
                                      << qPrintable(parseResult.errorMessage);
            return QString();
        }
        QDomElement settings = doc.documentElement();

        if (settings.isNull()) {
            return QString();
        }

        for (QDomElement e = settings.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
            if (e.tagName() == QLatin1StringView("folder")) {
                if (e.hasAttribute(u"type"_s)) {
                    if (e.attribute(u"type"_s) == QLatin1StringView("mh")) {
                        return QDir::homePath() + u'/' + e.attribute(u"path"_s);
                    }
                }
            }
        }
    }
    return QString();
}

bool FilterClawsMail::excludeFile(const QString &file)
{
    if (file.endsWith(QLatin1StringView(".claws_cache")) || file.endsWith(QLatin1StringView(".claws_mark"))
        || file.endsWith(QLatin1StringView(".mh_sequences"))) {
        return true;
    }
    return false;
}

QString FilterClawsMail::defaultInstallFolder() const
{
    return i18nc("define folder name where we will import clawsmail mails", "ClawsMail-Import") + u'/';
}

QString FilterClawsMail::markFile() const
{
    return u".claws_mark"_s;
}

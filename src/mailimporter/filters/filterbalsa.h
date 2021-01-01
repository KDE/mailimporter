/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FILTERBALSA_H
#define FILTERBALSA_H

#include "filters.h"
namespace MailImporter {
class FilterBalsaPrivate;
/**
 * @brief The FilterBalsa class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterBalsa : public Filter
{
public:
    FilterBalsa();
    ~FilterBalsa() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();
    QString localMailDirPath();
private:
    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    FilterBalsaPrivate *const d;
};
}

#endif // FILTERBALSA_H

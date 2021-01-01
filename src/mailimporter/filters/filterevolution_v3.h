/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILIMPORTER_FILTER_EVOLUTION_V3_H
#define MAILIMPORTER_FILTER_EVOLUTION_V3_H

#include "filters.h"
namespace MailImporter {
class FilterEvolution_v3Private;
/**
 * @brief The FilterEvolution_v3 class
 * @author Laurent Montel <montel@kde.org>
 */
class MAILIMPORTER_EXPORT FilterEvolution_v3 : public Filter
{
public:
    FilterEvolution_v3();
    ~FilterEvolution_v3() override;

    void import() override;
    void importMails(const QString &maildir);
    Q_REQUIRED_RESULT static QString defaultSettingsPath();
    Q_REQUIRED_RESULT static QString isMailerFound();

private:
    void importDirContents(const QString &);
    void importFiles(const QString &);
    void processDirectory(const QString &path);

    MailImporter::MessageStatus statusFromFile(const QString &filename);
    FilterEvolution_v3Private *const d;
};
}

#endif

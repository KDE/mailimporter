/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "mailimporter_private_export.h"
#include <QDialog>

#include <QMap>

namespace Ui
{
class SelectThunderbirdProfileWidget;
}

namespace MailImporter
{
class MAILIMPORTER_TESTS_EXPORT SelectThunderbirdProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectThunderbirdProfileWidget(QWidget *parent = nullptr);
    ~SelectThunderbirdProfileWidget();

    void fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile);
    [[nodiscard]] QString selectedProfile() const;

private:
    Ui::SelectThunderbirdProfileWidget *const ui;
};

class MAILIMPORTER_TESTS_EXPORT SelectThunderbirdProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectThunderbirdProfileDialog(QWidget *parent = nullptr);
    ~SelectThunderbirdProfileDialog();
    [[nodiscard]] QString selectedProfile() const;
    void fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile);

private:
    SelectThunderbirdProfileWidget *const mSelectProfile;
};
}

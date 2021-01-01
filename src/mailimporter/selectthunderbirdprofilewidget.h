/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTTHUNDERBIRDPROFILEWIDGET_H
#define SELECTTHUNDERBIRDPROFILEWIDGET_H

#include <QDialog>
#include "mailimporter_private_export.h"

#include <QMap>

namespace Ui {
class SelectThunderbirdProfileWidget;
}

namespace MailImporter {
class MAILIMPORTER_TESTS_EXPORT SelectThunderbirdProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectThunderbirdProfileWidget(QWidget *parent = nullptr);
    ~SelectThunderbirdProfileWidget();

    void fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile);
    Q_REQUIRED_RESULT QString selectedProfile() const;

private:
    Ui::SelectThunderbirdProfileWidget *const ui;
};

class MAILIMPORTER_TESTS_EXPORT SelectThunderbirdProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectThunderbirdProfileDialog(QWidget *parent = nullptr);
    ~SelectThunderbirdProfileDialog();
    Q_REQUIRED_RESULT QString selectedProfile() const;
    void fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile);

private:
    SelectThunderbirdProfileWidget *mSelectProfile = nullptr;
};
}

#endif // SELECTTHUNDERBIRDPROFILEWIDGET_H

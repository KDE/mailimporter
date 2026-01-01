/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectthunderbirdprofilewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ui_selectthunderbirdprofilewidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace MailImporter;

SelectThunderbirdProfileDialog::SelectThunderbirdProfileDialog(QWidget *parent)
    : QDialog(parent)
    , mSelectProfile(new SelectThunderbirdProfileWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Select thunderbird profile"));
    setModal(true);
    auto topLayout = new QVBoxLayout(this);

    mSelectProfile->setObjectName(QLatin1StringView("selectprofile"));
    topLayout->addWidget(mSelectProfile);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectThunderbirdProfileDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectThunderbirdProfileDialog::reject);
    topLayout->addWidget(buttonBox);
}

SelectThunderbirdProfileDialog::~SelectThunderbirdProfileDialog()
{
}

void SelectThunderbirdProfileDialog::fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile)
{
    mSelectProfile->fillProfile(map, defaultProfile);
}

QString SelectThunderbirdProfileDialog::selectedProfile() const
{
    return mSelectProfile->selectedProfile();
}

SelectThunderbirdProfileWidget::SelectThunderbirdProfileWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SelectThunderbirdProfileWidget)
{
    ui->setupUi(this);
}

SelectThunderbirdProfileWidget::~SelectThunderbirdProfileWidget()
{
    delete ui;
}

void SelectThunderbirdProfileWidget::fillProfile(const QMap<QString, QString> &map, const QString &defaultProfile)
{
    QMap<QString, QString>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        QString name = i.key();
        if (i.value() == defaultProfile) {
            name += i18n(" (default)");
        }
        ui->profile->addItem(name, i.value());
        ++i;
    }
}

QString SelectThunderbirdProfileWidget::selectedProfile() const
{
    return ui->profile->itemData(ui->profile->currentIndex()).toString();
}

#include "moc_selectthunderbirdprofilewidget.cpp"

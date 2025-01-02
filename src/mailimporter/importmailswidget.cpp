/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importmailswidget.h"
#include "ui_importmailswidget.h"

#include <QAbstractTextDocumentLayout>

using namespace MailImporter;

class MailImporter::ImportMailsWidgetPrivate
{
public:
    ImportMailsWidgetPrivate()
        : ui(new Ui::ImportMailsWidget)
    {
    }

    ~ImportMailsWidgetPrivate()
    {
        delete ui;
    }

    Ui::ImportMailsWidget *const ui;
};

ImportMailsWidget::ImportMailsWidget(QWidget *parent)
    : QWidget(parent)
    , d(new MailImporter::ImportMailsWidgetPrivate)
{
    d->ui->setupUi(this);
}

ImportMailsWidget::~ImportMailsWidget() = default;

void ImportMailsWidget::setStatusMessage(const QString &status)
{
    d->ui->textStatus->setText(status);
}

void ImportMailsWidget::setFrom(const QString &from)
{
    d->ui->from->setText(from);
}

void ImportMailsWidget::setTo(const QString &to)
{
    d->ui->to->setText(to);
}

void ImportMailsWidget::setCurrent(const QString &current)
{
    d->ui->current->setText(current);
}

void ImportMailsWidget::setCurrent(int percent)
{
    d->ui->done_current->setValue(percent);
}

void ImportMailsWidget::setOverall(int percent)
{
    d->ui->done_overall->setValue(percent);
}

void ImportMailsWidget::addItem(QListWidgetItem *item)
{
    d->ui->log->addItem(item);
}

void ImportMailsWidget::setLastCurrentItem()
{
    d->ui->log->setCurrentItem(d->ui->log->item(d->ui->log->count() - 1));
}

void ImportMailsWidget::addInfoLogEntry(const QString &log)
{
    d->ui->log->addInfoLogEntry(log);
}

void ImportMailsWidget::addErrorLogEntry(const QString &log)
{
    d->ui->log->addErrorLogEntry(log);
}

void ImportMailsWidget::clear()
{
    d->ui->log->clear();
    setCurrent(0);
    setOverall(0);
    setCurrent(QString());
    setFrom(QString());
    setTo(QString());
}

#include "moc_importmailswidget.cpp"

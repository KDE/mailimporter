/*
  SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterinfogui.h"

using namespace MailImporter;

FilterInfoGui::FilterInfoGui()
{
}

FilterInfoGui::~FilterInfoGui()
{
}

void FilterInfoGui::setStatusMessage(const QString &status)
{
    Q_UNUSED(status)
}

void FilterInfoGui::setFrom(const QString &from)
{
    Q_UNUSED(from)
}

void FilterInfoGui::setTo(const QString &to)
{
    Q_UNUSED(to)
}

void FilterInfoGui::setCurrent(const QString &current)
{
    Q_UNUSED(current)
}

void FilterInfoGui::setCurrent(int percent)
{
    Q_UNUSED(percent)
}

void FilterInfoGui::setOverall(int percent)
{
    Q_UNUSED(percent)
}

void FilterInfoGui::addErrorLogEntry(const QString &log)
{
    Q_UNUSED(log)
}

void FilterInfoGui::addInfoLogEntry(const QString &log)
{
    Q_UNUSED(log)
}

void FilterInfoGui::clear()
{
}

void FilterInfoGui::alert(const QString &message)
{
    Q_UNUSED(message)
}

QWidget *FilterInfoGui::parent() const
{
    return nullptr;
}

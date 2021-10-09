/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "filterinfo.h"
#include "filterinfogui.h"

using namespace MailImporter;

class Q_DECL_HIDDEN FilterInfo::FilterInfoPrivate
{
public:
    FilterInfoPrivate()
    {
    }

    ~FilterInfoPrivate()
    {
        delete m_filterInfoGui;
        m_filterInfoGui = nullptr;
    }

    bool m_removeDupMsg = false;
    FilterInfoGui *m_filterInfoGui = nullptr;
    static bool s_terminateASAP;
};

bool FilterInfo::FilterInfoPrivate::s_terminateASAP = false;

FilterInfo::FilterInfo()
    : d(new FilterInfoPrivate)
{
    FilterInfoPrivate::s_terminateASAP = false;
}

FilterInfo::~FilterInfo() = default;

void FilterInfo::setFilterInfoGui(FilterInfoGui *filterinfogui)
{
    delete d->m_filterInfoGui;
    d->m_filterInfoGui = filterinfogui;
}

void FilterInfo::setStatusMessage(const QString &status)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setStatusMessage(status);
    }
}

void FilterInfo::setFrom(const QString &from)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setFrom(from);
    }
}

void FilterInfo::setTo(const QString &to)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setTo(to);
    }
}

void FilterInfo::setCurrent(const QString &current)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setCurrent(current);
    }
}

void FilterInfo::setCurrent(int percent)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setCurrent(percent);
    }
}

void FilterInfo::setOverall(int percent)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->setOverall(percent);
    }
}

void FilterInfo::addInfoLogEntry(const QString &log)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->addInfoLogEntry(log);
    }
}

void FilterInfo::addErrorLogEntry(const QString &log)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->addErrorLogEntry(log);
    }
}

void FilterInfo::clear()
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->clear();
    }
}

void FilterInfo::alert(const QString &message)
{
    if (d->m_filterInfoGui) {
        d->m_filterInfoGui->alert(message);
    }
}

void FilterInfo::terminateASAP()
{
    FilterInfoPrivate::s_terminateASAP = true;
}

bool FilterInfo::shouldTerminate() const
{
    return FilterInfoPrivate::s_terminateASAP;
}

void FilterInfo::setRemoveDupMessage(bool removeDupMessage)
{
    d->m_removeDupMsg = removeDupMessage;
}

bool FilterInfo::removeDupMessage() const
{
    return d->m_removeDupMsg;
}

QWidget *FilterInfo::parentWidget() const
{
    if (d->m_filterInfoGui) {
        return d->m_filterInfoGui->parent();
    }
    return nullptr;
}

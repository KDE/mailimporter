/*
  SPDX-FileCopyrightText: 2000 Hans Dijkema <kmailcvt@hum.org>
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

// Local Includes

// KDE Includes
#include "filters.h"
#include "mailimporter_debug.h"
//////////////////////////////////////////////////////////////////////////////////
//
// The generic filter class
//
//////////////////////////////////////////////////////////////////////////////////

using namespace MailImporter;

class Q_DECL_HIDDEN Filter::FilterPrivate
{
public:
    FilterPrivate(const QString &_name, const QString &_author, const QString &_info)
        : name(_name)
        , author(_author)
        , info(_info)
    {
    }

    ~FilterPrivate()
    {
    }

    QString name;
    QString author;
    QString info;
    QString mailDir;
    MailImporter::FilterImporterBase *filterImporter = nullptr;
    MailImporter::FilterInfo *filterInfo = nullptr;
};

Filter::Filter(const QString &name, const QString &author, const QString &info)
    : d(new FilterPrivate(name, author, info))
{
}

Filter::~Filter() = default;

void Filter::clear()
{
    filterImporter()->clear();
    d->mailDir.clear();
}

void Filter::setMailDir(const QString &mailDir)
{
    d->mailDir = mailDir;
}

QString Filter::mailDir() const
{
    return d->mailDir;
}

void Filter::setFilterInfo(FilterInfo *info)
{
    d->filterInfo = info;
    clear();
}

MailImporter::FilterInfo *Filter::filterInfo() const
{
    if (!d->filterInfo) {
        Q_ASSERT_X(d->filterInfo != nullptr, "Filter::filterInfo", "filterInfo was not settings. It's a bug in application.");
        qCDebug(MAILIMPORTER_LOG) << " filterInfo must never be null. You forgot to create a filterinfo";
    }
    return d->filterInfo;
}

void Filter::setFilterImporter(FilterImporterBase *importer)
{
    d->filterImporter = importer;
}

FilterImporterBase *Filter::filterImporter() const
{
    Q_ASSERT_X(d->filterImporter != nullptr, "Filter::filterImporter", "filterImporter was not settings. It's a bug in application.");
    return d->filterImporter;
}

void Filter::clearCountDuplicate()
{
    filterImporter()->clearCountDuplicate();
}

int Filter::countDuplicates() const
{
    return filterImporter()->countDuplicates();
}

QString Filter::author() const
{
    return d->author;
}

QString Filter::name() const
{
    return d->name;
}

QString Filter::info() const
{
    return d->info;
}

void Filter::setAuthor(const QString &_author)
{
    d->author = _author;
}

void Filter::setName(const QString &_name)
{
    d->name = _name;
}

void Filter::setInfo(const QString &_info)
{
    d->info = _info;
}

bool Filter::importMessage(const QString &folderName, const QString &msgPath, bool duplicateCheck, const MailImporter::MessageStatus &status)
{
    return filterImporter()->importMessage(folderName, msgPath, duplicateCheck, status);
}

int Filter::countDirectory(const QDir &dir, bool searchHiddenDirectory)
{
    int countDir = 0;
    QStringList subDirs;
    if (searchHiddenDirectory) {
        subDirs = dir.entryList(QStringList(QStringLiteral("*")), QDir::Dirs | QDir::Hidden, QDir::Name);
    } else {
        subDirs = dir.entryList(QStringList(QStringLiteral("[^\\.]*")), QDir::Dirs, QDir::Name); // Removal of . and ..
    }

    QStringList::ConstIterator end = subDirs.constEnd();
    for (QStringList::ConstIterator filename = subDirs.constBegin(); filename != end; ++filename) {
        if (!(*filename == QLatin1Char('.') || *filename == QLatin1String(".."))) {
            countDir += countDirectory(QDir(dir.filePath(*filename)), searchHiddenDirectory) + 1;
        }
    }
    return countDir;
}

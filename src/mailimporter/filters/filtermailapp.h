/***************************************************************************
                          filter_mailapp.h  -  OS X Mail App import
                             -------------------
    copyright            : (C) 2004 by Chris Howells
    email                : howells@kde.org

    Derived from code by:
    copyright            : (C) 2003 by Laurence Anderson
    email                : l.d.anderson@warwick.ac.uk

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAILIMPORTER_FILTER_MAILAPP_H
#define MAILIMPORTER_FILTER_MAILAPP_H

#include "filters.h"
namespace MailImporter {
class FilterMailAppPrivate;
/**
 *imports mbox archives messages into KMail
 *@author Chris Howells
 */
class MAILIMPORTER_EXPORT FilterMailApp : public Filter
{
public:
    FilterMailApp();
    ~FilterMailApp() override;

    void import() override;
    void importMails(const QString &maildir);
private:
    FilterMailAppPrivate *const d;
    void traverseDirectory(const QString &);
};
}

#endif

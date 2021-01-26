/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MAILIMPORTERPRIVATE_EXPORT_H
#define MAILIMPORTERPRIVATE_EXPORT_H

#include "mailimporter_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef MAILIMPORTER_TESTS_EXPORT
#define MAILIMPORTER_TESTS_EXPORT MAILIMPORTER_EXPORT
#endif
#else /* not compiling tests */
#define MAILIMPORTER_TESTS_EXPORT
#endif

#endif

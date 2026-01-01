/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "selectthunderbirdprofiledialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../selectthunderbirdprofilewidget.h"

#include <QDialogButtonBox>
#include <QTest>

SelectThunderbirdProfileDialogTest::SelectThunderbirdProfileDialogTest(QObject *parent)
    : QObject(parent)
{
}

void SelectThunderbirdProfileDialogTest::shouldHaveDefaultValue()
{
    MailImporter::SelectThunderbirdProfileDialog dlg;
    auto widget = dlg.findChild<MailImporter::SelectThunderbirdProfileWidget *>(u"selectprofile"_s);
    QVERIFY(widget);
    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

QTEST_MAIN(SelectThunderbirdProfileDialogTest)

#include "moc_selectthunderbirdprofiledialogtest.cpp"

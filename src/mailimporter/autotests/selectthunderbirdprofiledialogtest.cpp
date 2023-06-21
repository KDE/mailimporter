/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "selectthunderbirdprofiledialogtest.h"
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
    auto widget = dlg.findChild<MailImporter::SelectThunderbirdProfileWidget *>(QStringLiteral("selectprofile"));
    QVERIFY(widget);
    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}

QTEST_MAIN(SelectThunderbirdProfileDialogTest)

#include "moc_selectthunderbirdprofiledialogtest.cpp"

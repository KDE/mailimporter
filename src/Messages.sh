#! /bin/sh
$EXTRACTRC `find . -name '*.ui'` >> rc.cpp || exit 11
$XGETTEXT `find . -name '*.cpp' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/libmailimporter.pot
rm -f rc.cpp

/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "filterimporterbase.h"
#include "filterinfo.h"
#include "filterinfogui.h"
#include "filters.h"
#include "filters/filterbalsa.h"
#include "filters/filterclawsmail.h"
#include "filters/filterevolution.h"
#include "filters/filterevolution_v2.h"
#include "filters/filterevolution_v3.h"
#include "filters/filtericedove.h"
#include "filters/filterkmail_maildir.h"
#include "filters/filterkmailarchive.h"
#include "filters/filterlnotes.h"
#include "filters/filtermailapp.h"
#include "filters/filtermailmangzip.h"
#include "filters/filtermbox.h"
#include "filters/filteroe.h"
#include "filters/filteropera.h"
#include "filters/filterplain.h"
#include "filters/filterpmail.h"
#include "filters/filterseamonkey.h"
#include "filters/filtersylpheed.h"
#include "filters/filterthebat.h"
#include "filters/filterthunderbird.h"
#include "importmailswidget.h"
#include "mailimporter_private_export.h"
#include "mailimporter_utils.h"
#include "messagestatus.h"
#include "othermailerutil.h"
#include "selectthunderbirdprofilewidget.h"

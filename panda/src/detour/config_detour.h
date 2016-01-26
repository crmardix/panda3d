// Filename: config_detour.h
// Created by:  sennoma (25Jan16)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef CONFIG_DETOUR_H
#define CONFIG_DETOUR_H

#include "pandabase.h"

#include "notifyCategoryProxy.h"
#include "dconfig.h"

ConfigureDecl(config_detour, EXPCL_DETOUR, EXPTP_DETOUR);
NotifyCategoryDecl(detour, EXPCL_DETOUR, EXPTP_DETOUR);

extern EXPCL_DETOUR void init_libdetour();

#endif

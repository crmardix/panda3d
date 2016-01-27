// Filename: detourNavMeshNode.h
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

#ifndef DETOURNAVMESHNODE_H
#define DETOURNAVMESHNODE_H

#include "config_detour.h"
#include "pandaNode.h"
#include "geomNode.h"

#include <DetourNavMesh.h>

class DetourNavMeshNode;

////////////////////////////////////////////////////////////////////
//       Class : DetourNavMeshNode
// Description : PandaNode which contains navigation mesh data
////////////////////////////////////////////////////////////////////
class EXPCL_DETOUR DetourNavMeshNode : public PandaNode {
PUBLISHED:
  DetourNavMeshNode(const string &name, const string &data, const int flags);
  virtual ~DetourNavMeshNode();

private:
  PT(GeomNode) _viz_geom;
  dtNavMesh _nav_mesh;

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    PandaNode::init_type();
    register_type(_type_handle, "DetourNavMeshNode",
                  PandaNode::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;

};

#endif

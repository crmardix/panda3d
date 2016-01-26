// Filename: detourNavMeshNode.cxx
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

#include "detourNavMeshNode.h"

TypeHandle DetourNavMeshNode::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: DetourNavMeshNode::Constructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
DetourNavMeshNode::
DetourNavMeshNode(const string &name, const string &data, const int flags) : PandaNode(name) {
  _viz_geom = NULL;
  _nav_mesh = NULL;
  const int data_size = name.size();
  unsigned char *data_char = new unsigned char[data_size * 2];
  strcpy(data_char, name.c_str());
  _nav_mesh = new dtNavMesh();
  _nav_mesh::init(data_char, data_size, flags);
}

////////////////////////////////////////////////////////////////////
//     Function: DetourNavMeshNode::Destructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
DetourNavMeshNode::
~DetourNavMeshNode() {
  if (_nav_mesh) {
    dtFreeNavMesh(_nav_mesh);
  }
}

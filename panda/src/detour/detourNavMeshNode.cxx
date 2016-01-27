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
  _nav_mesh.init((unsigned char *)data.data(), data.size(), flags);
}

////////////////////////////////////////////////////////////////////
//     Function: DetourNavMeshNode::Destructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
DetourNavMeshNode::
~DetourNavMeshNode() {
}

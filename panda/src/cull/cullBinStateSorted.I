// Filename: cullBinStateSorted.I
// Created by:  drose (22Mar05)
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


////////////////////////////////////////////////////////////////////
//     Function: CullBinStateSorted::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE CullBinStateSorted::
CullBinStateSorted(const string &name, GraphicsStateGuardianBase *gsg,
                   const PStatCollector &draw_region_pcollector) :
  CullBin(name, BT_state_sorted, gsg, draw_region_pcollector),
  _objects(get_class_type())
{
}

////////////////////////////////////////////////////////////////////
//     Function: CullBinStateSorted::ObjectData::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE CullBinStateSorted::ObjectData::
ObjectData(CullableObject *object) :
  _object(object)
{
  if (object->_munged_data == NULL) {
    _format = NULL;
  } else {
    _format = object->_munged_data->get_format();
  }
}

////////////////////////////////////////////////////////////////////
//     Function: CullBinStateSorted::ObjectData::operator <
//       Access: Public
//  Description: Specifies the correct sort ordering for these
//               objects.
////////////////////////////////////////////////////////////////////
INLINE bool CullBinStateSorted::ObjectData::
operator < (const ObjectData &other) const {
  // Group by state changes, in approximate order from heaviest
  // change to lightest change.
  const RenderState *sa = _object->_state;
  const RenderState *sb = other._object->_state;
  int compare = sa->compare_sort(*sb);
  if (compare != 0) {
    return compare < 0;
  }

  // Vertex format changes are also fairly slow.
  if (_format != other._format) {
    return _format < other._format;
  }

  // Prevent unnecessary vertex buffer rebinds.
  if (_object->_munged_data != other._object->_munged_data) {
    return _object->_munged_data < other._object->_munged_data;
  }

  // Uniform updates are actually pretty fast.
  if (_object->_internal_transform != other._object->_internal_transform) {
    return _object->_internal_transform < other._object->_internal_transform;
  }

  return 0;
}


// Filename: cppMakeProperty.cxx
// Created by:  rdb (18Sep14)
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

#include "cppMakeProperty.h"
#include "cppFunctionGroup.h"

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
CPPMakeProperty::
CPPMakeProperty(CPPIdentifier *ident,
                CPPFunctionGroup *getter, CPPFunctionGroup *setter,
                CPPScope *current_scope, const CPPFile &file) :
  CPPDeclaration(file),
  _ident(ident),
  _has_function(NULL),
  _get_function(getter),
  _set_function(setter),
  _clear_function(NULL)
{
  _ident->_native_scope = current_scope;
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
CPPMakeProperty::
CPPMakeProperty(CPPIdentifier *ident,
                CPPFunctionGroup *hasser, CPPFunctionGroup *getter,
                CPPFunctionGroup *setter, CPPFunctionGroup *clearer,
                CPPScope *current_scope, const CPPFile &file) :
  CPPDeclaration(file),
  _ident(ident),
  _has_function(hasser),
  _get_function(getter),
  _set_function(setter),
  _clear_function(clearer)
{
  _ident->_native_scope = current_scope;
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::get_simple_name
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
string CPPMakeProperty::
get_simple_name() const {
  return _ident->get_simple_name();
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::get_local_name
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
string CPPMakeProperty::
get_local_name(CPPScope *scope) const {
  return _ident->get_local_name(scope);
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::get_fully_scoped_name
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
string CPPMakeProperty::
get_fully_scoped_name() const {
  return _ident->get_fully_scoped_name();
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::output
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
void CPPMakeProperty::
output(ostream &out, int indent_level, CPPScope *scope, bool complete) const {
  out << "__make_property";

  if (_has_function != NULL) {
    out.put('2');
  }

  out << "(" << _ident->get_local_name(scope);

  if (_has_function != NULL) {
    out << ", " << _has_function->_name;
  }

  out << ", " << _get_function->_name;

  if (_set_function != NULL) {
    out << ", " << _set_function->_name;
  }

  if (_clear_function != NULL) {
    out << ", " << _clear_function->_name;
  }

  out << ");";
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::get_subtype
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
CPPDeclaration::SubType CPPMakeProperty::
get_subtype() const {
  return ST_make_property;
}

////////////////////////////////////////////////////////////////////
//     Function: CPPMakeProperty::as_make_property
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
CPPMakeProperty *CPPMakeProperty::
as_make_property() {
  return this;
}

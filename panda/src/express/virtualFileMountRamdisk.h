// Filename: virtualFileMountRamdisk.h
// Created by:  drose (19Sep11)
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

#ifndef VIRTUALFILEMOUNTRAMDISK_H
#define VIRTUALFILEMOUNTRAMDISK_H

#include "pandabase.h"

#include "virtualFileMount.h"
#include "mutexImpl.h"
#include "streamWrapper.h"

////////////////////////////////////////////////////////////////////
//       Class : VirtualFileMountRamdisk
// Description : Simulates an actual directory on disk with in-memory
//               storage.  This is useful mainly for performing high
//               level functions that expect disk I/O without actually
//               writing files to disk.  Naturally, there are
//               significant limits to the size of the files that may
//               be written with this system; and "files" written here
//               are not automatically persistent between sessions.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAEXPRESS VirtualFileMountRamdisk : public VirtualFileMount {
PUBLISHED:
  VirtualFileMountRamdisk();

public:
  virtual bool has_file(const Filename &file) const;
  virtual bool create_file(const Filename &file);
  virtual bool make_directory(const Filename &file);
  virtual bool delete_file(const Filename &file);
  virtual bool rename_file(const Filename &orig_filename, const Filename &new_filename);
  virtual bool copy_file(const Filename &orig_filename, const Filename &new_filename);
  virtual bool is_directory(const Filename &file) const;
  virtual bool is_regular_file(const Filename &file) const;
  virtual bool is_writable(const Filename &file) const;

  virtual istream *open_read_file(const Filename &file) const;
  virtual ostream *open_write_file(const Filename &file, bool truncate);
  virtual ostream *open_append_file(const Filename &file);
  virtual iostream *open_read_write_file(const Filename &file, bool truncate);
  virtual iostream *open_read_append_file(const Filename &file);

  virtual streamsize get_file_size(const Filename &file, istream *stream) const;
  virtual streamsize get_file_size(const Filename &file) const;
  virtual time_t get_timestamp(const Filename &file) const;

  virtual bool scan_directory(vector_string &contents, 
                              const Filename &dir) const;

  virtual bool atomic_compare_and_exchange_contents(const Filename &file, string &orig_contents, const string &old_contents, const string &new_contents);
  virtual bool atomic_read_contents(const Filename &file, string &contents) const;

  virtual void output(ostream &out) const;

private:
  class FileBase;
  class File;
  class Directory;

  class FileBase : public TypedReferenceCount {
  public:
    INLINE FileBase(const string &basename);
    virtual ~FileBase();
    INLINE bool operator < (const FileBase &other) const;

    virtual bool is_directory() const;

    string _basename;
    time_t _timestamp;

  public:
    virtual TypeHandle get_type() const {
      return get_class_type();
    }
    virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
    static TypeHandle get_class_type() {
      return _type_handle;
    }
    static void init_type() {
      TypedReferenceCount::init_type();
      register_type(_type_handle, "VirtualFileMountRamdisk::FileBase",
                    TypedReferenceCount::get_class_type());
    }

  private:
    static TypeHandle _type_handle;
  };

  class File : public FileBase {
  public:
    INLINE File(const string &basename);

    stringstream _data;
    StreamWrapper _wrapper;

  public:
    virtual TypeHandle get_type() const {
      return get_class_type();
    }
    virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
    static TypeHandle get_class_type() {
      return _type_handle;
    }
    static void init_type() {
      FileBase::init_type();
      register_type(_type_handle, "VirtualFileMountRamdisk::File",
                    FileBase::get_class_type());
    }

  private:
    static TypeHandle _type_handle;
  };

  typedef pset<PT(FileBase), indirect_less<FileBase *> > Files;

  class Directory : public FileBase {
  public:
    INLINE Directory(const string &basename);

    virtual bool is_directory() const;

    PT(FileBase) do_find_file(const string &filename) const;
    PT(File) do_create_file(const string &filename);
    PT(Directory) do_make_directory(const string &filename);
    PT(FileBase) do_delete_file(const string &filename);
    bool do_scan_directory(vector_string &contents) const;

    Files _files;

  public:
    virtual TypeHandle get_type() const {
      return get_class_type();
    }
    virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
    static TypeHandle get_class_type() {
      return _type_handle;
    }
    static void init_type() {
      FileBase::init_type();
      register_type(_type_handle, "VirtualFileMountRamdisk::Directory",
                    FileBase::get_class_type());
    }

  private:
    static TypeHandle _type_handle;
  };

  Directory _root;
  mutable MutexImpl _lock;

public:
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    VirtualFileMount::init_type();
    register_type(_type_handle, "VirtualFileMountRamdisk",
                  VirtualFileMount::get_class_type());
    FileBase::init_type();
    File::init_type();
    Directory::init_type();
  }

private:
  static TypeHandle _type_handle;
};

#include "virtualFileMountRamdisk.I"

#endif

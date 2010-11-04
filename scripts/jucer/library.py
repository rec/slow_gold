#!/usr/local/bin/python

# Representation of external libraries for Juce.
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
#
# Essentially, you can do as you please with it.  Have fun!

"""
    <XCODE_MAC extraLinkerFlags="-L../../../../../build/debug/libcddb/lib -lcddb -L../../../../../build/debug/gflags/lib -lgflags -L../../../../../build/debug/glog/lib -lglog -L../../../../../build/debug/gtest/lib -lgtest -lgtest_main -L../../../../../build/debug/iconv/lib -liconv -L../../../../../build/debug/mpg123/lib -lmpg123 -L../../../../../build/debug/protobuf/lib -lprotobuf"

            extraLinkerFlags="libcddb.lib libgflags-debug.lib libglog.lib libmpg123.lib libprotobuf.lib /LIBPATH:..\..\..\..\..\libcddb-1.3.2\Debug /LIBPATH:..\..\..\..\..\gflags-1.3\Debug /LIBPATH:..\..\..\..\..\glog-0.3.1\Debug /LIBPATH:..\..\..\..\..\mpg123-1.12.5\ports\MSVC++\2008\Debug /LIBPATH:..\..\..\..\..\protobuf-2.3.0\vsprojects\Debug /NODEFAULTLIB:MSVCRTD /NODEFAULTLIB:msvcprtd""""

class Library:
  """Represents an external library or facility within the Jucer."""

  def __init__(self, name, **kwds):
    """Construct with a name, and the following keywords and default:
      header_only=False,      # Is this library only used for its headers?
      libraries=[self.name],  # A list of library names for this library.
      include='/include',     # The subdirectory for finding include files.
      relative=True,          # Is this path relative to the config directory?
      use_config=False,       # Do we use config as part of the path (WIN32)?
      win_nodefaultlib=False  # Is this a Windows /NODEFAULTLIB flag?
    """
    self.name = name
    self.kwds = kwds


  def get(self, **kwds):
    for k, v in kwds.iteritems():
      return self.kwds.get(k, v)


  def link(self, root, config, is_windows=False):
    if self.get(header_only=False):
      return False

    if self.get(win_nodefaultlib=False):
      return is_windows and '/NODEFAULTLIB:%s' % name

    if is_windows:
      lib_format = 'lib%s.lib'
      libpath_format = '/LIBPATH:%s\\%s\\%s'
    else:
      lib_format = '-l%s'
      libpath_format = '-L%s/%s/%s/lib'

    libraries = [lib_format % lib for lib in self.get(libraries=[self.name])]
    if not self.get(system=False):
      libraries.insert(0, libpath_format % (root, config, self.name))

    return ' '.join(libraries)


  def header(self, root, config, is_windows=False):
    if self.get(win_nodefaultlib=False) or not self.get(header_needed=True):
      return ''

    elif not self.get(relative=True):
      return self.name

    elif self.get(header_only=False):
      return '%s/%s' % (root, self.name)

    else:
      return '%s/%s/%s%s' % (root, config, self.name,
                             self.get(include='/include'))


def getHeaders(libraries, root, config):
  return filter(None, (i.header(root, config) for i in libraries))


def getLinks(libraries, root, config):
  return filter(None, (i.link(root, config) for i in libraries))





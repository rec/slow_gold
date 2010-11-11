#!/usr/local/bin/python

# Representation of external libraries for Juce.
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
#
# Essentially, you can do as you please with it.  Have fun!


PACKAGE_DEFAULT = dict(
  header='build/{0}/{name}{include}',  # A format string for header paths.
  header_needed=True,      # Packages that require a header.
  header_only=False,       # Is this library only used for its headers?
  include='/include',      # The subdirectory for finding include files.
  libraries=None,          # A list of library names for this library.
  name=None,               # Name of the library.
  relative=True,           # Is this path relative to the config directory?
  use_config=False,        # Do we use config as part of the path (WIN32)?
  win_extralinkpath='',    # extra path elements for windows only.
  win_header=None,         # Override header string for Windows only.
  win_nodefaultlib=False,  # Is this a Windows /NODEFAULTLIB flag?
)


HEADER_ROOT = '../../../../../'


PLATFORM = dict(
  mac=dict(
    is_windows=False,
    library='-l{0}',
    library_path='-L../../../../../build/{0}/{name}/lib',
    nodefaultlib='',
    ),

  win=dict(
    is_windows=True,
    library='lib{0}.lib',
    library_path=r'/LIBPATH:..\..\..\..\..\{name}{win_extralinkpath}\{0}',
    nodefaultlib='/NODEFAULTLIB:{name}',
    ),
  )


def get(package, name, dflt=None):
  return package.get(name, dflt or PACKAGE_DEFAULT.get(name, None))


def fmt(fmt_string, package, config):
  p = dict(**PACKAGE_DEFAULT)
  p.update(package)
  return fmt_string.format(config, **p)


def header(package, platform, config):
  if type(platform) is str:
    platform = PLATFORM[platform]

  if get(package, 'win_nodefaultlib') or not get(package, 'header_needed'):
    return ''

  if not get(package, 'relative'):
    return get(package, 'name')

  header = (platform['is_windows'] and get(package, 'win_header')
            ) or get(package, 'header')
  return HEADER_ROOT + fmt(header, package, config)


def link(package, platform, config):
  if type(platform) is str:
    platform = PLATFORM[platform]

  if get(package, 'header_only'):
    return ''

  if get(package, 'win_nodefaultlib'):
    return platform['nodefaultlib'].format(**package)

  libraries = get(package, 'libraries', [get(package, 'name')])
  libraries = [platform['library'].format(i) for i in libraries]
  if not get(package, 'system'):
    libraries.insert(0, fmt(platform['library_path'], package, config))

  return ' '.join(libraries)

#!/usr/local/bin/python

import os
import sys

import get_os
import parse_options


FLAGS = (
  ('name', {}),
  ('version', {}),
  ('cwd', {'default': os.getcwd()}),
  ('os', {'default': get_os.get_os()}),
  ('suffix', {'default': '.tar.bz2'}),
  ('config_flags', {'default': '--with-cpu=x86  --enable-static --enable-shared=no'}),
  ('directory', {'default': '{name}-{version}'}),
  ('archive', {'default': '{directory}{suffix}'}),
  ('extract', {'default': 'tar xzf {archive}'}),
  ('path', {}),
  ('url', {'default': 'http://{path}/{archive}'}),
  ('download', {'default': 'wget {url}'}),
  ('configure', {'default':  './configure {config_flags}'}),
  )


USAGE_MESSAGE = """Usage:
    fetch.py --name=NAME --version=VERSION [optional flags]

Type
    fetch.py --help
for more information on the optional flags.
"""


def parse(argv=None, parser=None):
  try:
    return parse_options.parse_options(FLAGS, argv, parser)
  except:
    sys.stderr.write(USAGE_MESSAGE)
    raise


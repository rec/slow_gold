#!/usr/local/bin/python

import optparse
import sys

def parse_options(flags, argv=None, parser=None):
  """Parse the given options, expand their templates in order, and return the
  options and any remaining flags.

  >>> parse_options((), [])
  ({}, [])

  >>> parse_options((('a', {}), ('b', {'default': '/tmp'})), [])
  ({'a': '', 'b': '/tmp'}, [])

  """
  if argv is None:
    argv = sys.argv[1:]

  parser = parser or optparse.OptionParser()

  for name, keywords in flags:
    parser.add_option('--' + name, dest=name, **keywords)

  options, args = parser.parse_args(argv)
  options = vars(options)
  for name, value in flags:
    options[name] = (options[name] or "").format(**options)

  return options, args


if __name__ == "__main__":
  import doctest
  doctest.testmod()

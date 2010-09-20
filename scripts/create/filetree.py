#!/usr/local/bin/python

import os
import stat

import odict


def filetree(file, accept):
  try:
    st_mode = os.lstat(file).st_mode

  except OSError:
    print 'os.error, skipped file', file
    return

  if stat.S_ISDIR(st_mode):
    values = odict.OrderedDict()
    for name in os.listdir(file):
      tree = filetree(os.path.join(file, name), accept)
      if tree:
        values[name] = tree

    return values

  elif stat.S_ISREG(st_mode) and accept(file):
    return file

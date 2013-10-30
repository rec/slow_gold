#!/usr/bin/env python

from __future__ import absolute_import, division, print_function, unicode_literals

import re
import shutil
import sys

def rewrite(filename, bracketing, replacement):
  tmp_file = '%s.bak' % filename
  match = re.compile('%s(.*?)%s' % (bracketing, bracketing))
  replacement = ''.join([bracketing, replacement, bracketing])
  changes = 0

  with open(filename, 'rb') as f_in:
    with open(tmp_file, 'wb') as f_out:
      for line in f_in:
        print('!!', line)
        s, count = match.subn(replacement, line)
        f_out.write(s)
        changes += count

  shutil.move(tmp_file, filename)
  return changes

if __name__ == '__main__':
  if len(sys.argv) != 4:
    print('Usage: rewrite FILENAME BRACKETING REPLACEMENT')
    exit(-1)

  filename, bracketing, replacement = sys.argv[1:]
  changes = rewrite(filename, bracketing, replacement)
  print('File %s rewritten with %d change%s.' % (
    filename, changes, '' if changes == 1 else 's' ))

#!/usr/local/bin/python

import glob
import os
import os.path
import re
import sys

import util

IGNORE_STRINGS = [r'#if',
                  r'#define',
                  r'#endif',
                  r'#include\s+',
                  r'class\s',
                  r'\s*public:',
                  r'\s*private:',
                  r'\s*DISALLOW_',
                  r'  static const ',
                  r'};',
                  ]

IGNORE_PATTERNS = [re.compile('^' + s) for s in IGNORE_STRINGS]

def mustIgnore(s, patterns=IGNORE_PATTERNS):
  for p in patterns:
    if p.match(s):
      return True

  return False

REMOVE_WORDS = ['virtual ', 'explicit ']

def removeWords(s):
  for w in REMOVE_WORDS:
    s = s.replace(w, '')
  return s


def Check(f, t):
  f, t = os.path.abspath(f), os.path.abspath(t)

  if not os.path.exists(f):
    raise ValueError(f + " doesn't exist!")

  if os.path.isdir(f):
    raise ValueError(f + ' is a directory!')

  if os.path.exists(t):
    raise ValueError(t + ' already exists.')

  return f, t

def ProcessLines(input, hfile):
  filename = hfile.split('/rec/src/')[-1]
  yield '#include "%s"\n' % filename
  cname = filename.split('/')[-1].split('.h')[0]
  dname = '~' + cname
  yield '\n'
  hasData = False
  for line in input:
    if not mustIgnore(line):
      if line.startswith('  '):
        line = line[2:]
      line = removeWords(line)
      hadData = hasData
      hasData = line.strip()
      if hasData or hadData:
        if dname in line:
          yield line.replace(dname, '%s::%s' % (cname, dname))
        else:
          yield line.replace('%s(' % cname, '%s::%s(' % (cname, cname))

def SplitCpp(h):
  if not h.endswith('.h'):
    h += '.h'
  h, cpp = Check(h, h[:-2] + '.cpp')
  with open(h) as input:
    with open(cpp, 'w') as output:
      for line in ProcessLines(input, h):
        output.write(line)
  return cpp

if __name__ == '__main__':
  if len(sys.argv) is 2:
    print 'Wrote', SplitCpp(sys.argv[1])
  else:
    print 'Usage: SplitCpp.py header-file-name'

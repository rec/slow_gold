#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: revise oldfile"""

def revise(oldfile):
  old = translate.readStrings(oldfile)
  for s in old.str:
    print translate.stringName(s)
    print '"%s"' % proto.encode(s.translation)
    t = proto.input()
    if t:
      s.translation = t
  return old


if __name__ == '__main__':
  if len(sys.argv) is 2:
    proto.write(revise(sys.argv[1]))
  else:
    print USAGE


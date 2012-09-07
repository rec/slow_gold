#!/usr/local/bin/python

import sys

import proto
import translate

USAGE = """Usage: fill oldfile"""

def fill(oldfile):
  old = translate.readStrings(oldfile)
  for s in old.str:
    if not s.translation:
      print translate.stringName(s)
      t = proto.input()
      if t:
        s.translation = t
  return old


if __name__ == '__main__':
  if len(sys.argv) is 2:
    proto.write(revise(sys.argv[1]))
  else:
    print USAGE


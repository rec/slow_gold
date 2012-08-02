#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: merge protofile translationfile"""

FIXES = (
  ('"% s"', '"%s"'),
  ('(% s)', '(%s)'),
  ('% S', '%s'),
  ('% s', ' %s'),
  ('% d', ' %d'),
  )

def fixStrings(s):
  for f in FIXES:
    s = s.replace(*f);
  return s

def mergeNewTranslation(oldfile, newtext):
  oldstrings = translate.readStrings(oldfile)
  newlines = open(newtext, 'r').readlines()
  for old, new in zip(oldstrings.str, newlines):
    old.translation = fixStrings(proto.decode(new.strip()))
  return oldstrings

if __name__ == '__main__':
  if len(sys.argv) is 3:
    mt = mergeNewTranslation(*sys.argv[1:])
    print proto.toString(mt)

  else:
    print USAGE

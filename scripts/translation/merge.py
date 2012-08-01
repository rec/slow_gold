#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: merge protofile translationfile"""

def mergeNewTranslation(oldfile, newtext):
  oldstrings = proto.read(translate.TranslatedStrings, oldfile)
  newlines = open(newtext, 'r').readlines()
  for old, new in zip(oldstrings.str, newlines):
    old.original = proto.decode(new.strip())

  return oldstrings

if __name__ == '__main__':
  if len(sys.argv) is 3:
    proto.write(mergeNewTranslation(*sys.argv[1:]))
  else:
    print USAGE


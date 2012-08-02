#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: list.py protofile"""
PRINT_LINE_NUMBERS = False

def printCurrentTranslation(oldfile):
  old = translate.readStrings(oldfile)
  for i, x in enumerate(old.str):
    s = proto.encode(x.translation)
    if PRINT_LINE_NUMBERS:
      print '%d: %s' % (i, s)
    else:
      print s

if __name__ == '__main__':
  if len(sys.argv) is 2:
    printCurrentTranslation(sys.argv[1])
  else:
    print USAGE


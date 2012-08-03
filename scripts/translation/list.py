#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: list.py protofile"""
PRINT_LINE_NUMBERS = False
PRINT_TRANSLATION = False

def printOriginal(oldfile):
  old = translate.readStrings(oldfile)
  for x in old.str:
    if PRINT_TRANSLATION or not x.translation:
      s = proto.encode(x.original)
      if x.index:
        print '%d: %s' % (x.index, s)
      else:
        print s

if __name__ == '__main__':
  if len(sys.argv) is 2:
    printOriginal(sys.argv[1])
  else:
    print USAGE


#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: update oldfile newfile"""

if __name__ == '__main__':
  if len(sys.argv) is 3:
    proto.write(translate.readNewTranslations(*sys.argv[1:]))
  else:
    print USAGE


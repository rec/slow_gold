#!/usr/bin/python

import sys

import translate

USAGE = """Usage: list.py protofile"""

if __name__ == '__main__':
  if len(sys.argv) is 2:
    translate.printCurrentTranslation(sys.argv[1])
  else:
    print USAGE


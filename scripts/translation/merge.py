#!/usr/bin/python

import sys

import translate

USAGE = """Usage: merge protofile translationfile"""

if __name__ == '__main__':
  if len(sys.argv) is 3:
    t = translate.readNewTranslations(*sys.argv[1:])
    text_format.PrintMessage(t, sys.stdout)

  else:
    print USAGE


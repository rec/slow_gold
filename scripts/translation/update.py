#!/usr/bin/python

import sys

import translate

USAGE = """Usage: update oldfile newfile"""

if __name__ == '__main__':
  if len(sys.argv) is 3:
    t = translate.readNewTranslations(*sys.argv[1:])
    text_format.PrintMessage(t, sys.stdout)

  else:
    print USAGE


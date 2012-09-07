#!/usr/local/bin/python

import sys

import extractUntranslated
import mergeIncoming

USAGE = """Usage: merge [rootDirectory]"""

def merge(root):
  mergeIncoming.mergeIncoming(root)
  extractUntranslated.extractUntranslated(root)


if __name__ == '__main__':
  if len(sys.argv) <= 2:
    merge(sys.argv[1:])
  else:
    print USAGE


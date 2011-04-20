#!/usr/bin/python

ROOT = '/Users/tom/Documents/development/rec/scripts/new/templates/'

GROUPS = [['.cpp'],
          ['.h'],
          ['.proto'],
          ['_test.cpp'],
          ['.svg', '.svg.h', '.svg.cpp']]


def getGroups():
  return [isinstance(s, str) and s or s[0] for s in GROUPS]

def getGroupTemplate(suffix):
  for g in GROUPS:
    if suffix == g[0]:
      g += [g[0], g[0]]
      return g[1], open(ROOT + g[2], 'r').read()



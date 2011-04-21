#!/usr/bin/python

import optparse
import sys

import groups
import split

GROUPS = groups.getGroups()
USAGE = """\
Usage:

  new [--svg=<svg-file>] <group> [...<group>] <name>

where
  <svg-file> is a path to an SVG file.
  <group> is one of %s

The --svg flag is only required if one of the groups is svg.
""" % ', '.join(GROUPS)

def usageError():
  print USAGE
  raise ValueError

def readSVGFile(f):
  svg = '"%s\\n"' % (open(f).read().replace('"', '\\"')
                     .replace('\n', '\\n"\n  "'))
  return ''.join(split.splitLargeLines(svg.split('\n')))

def splitGroup(filename):
  for g in GROUPS:
    if filename.endswith(g):
      return filename[0:len(filename) - len(g)], g
  return filename, ''

def splitGroupArgs(args):
  lastFile = None
  lastSuffix = None
  files = []
  for a in args:
    file, suffix = splitGroup(a)

    if file:
      lastFile = file
      files.append(file)

    if suffix:
      lastSuffix = suffix
      if files:
        for f in files:
          yield f, suffix
        files = []
      else:
        if lastFile:
          yield lastFile, suffix
        lastFile = None

  if files:
    if lastSuffix:
      for f in files:
        yield f, lastSuffix
    else:
      raise ValueError("Couldn't guess suffix from " + str(args))

def parseArgs():
  parser = optparse.OptionParser()
  parser.add_option('--svg', dest='svg')
  options, args = parser.parse_args()
  context = {'args': ' '.join(sys.argv[1:]), 'cmd': sys.argv[0]}
  if options.svg:
    context.update(svg=readSVGFile(options.svg),
                   svg_file=options.svg)

  return list(splitGroupArgs(args)), context


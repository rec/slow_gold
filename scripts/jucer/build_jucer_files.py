#!/usr/bin/python
#
# Handle .jucer files!
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
#
# Essentially, you can do as you please with it.  Have fun!

import os
import sys

import jucer

DEFAULT_PROJECTS = 'command', 'slow', 'tests', 'support'

def buildOne(name):
  root = os.getenv('ROOT')
  base = name.split('.')[0]
  doc = '%s/rec/projects/%s/%s.jucer' % (root, base, name)

  results = jucer.JucerDomFile(doc, 'test' in name, root).toxml()
  f = open(doc, 'w')
  for line in results.split('\n'):
    if line.strip():
      f.write(line)
      f.write('\n')
  print 'Written', doc

def build(names):
  for name in (names or DEFAULT_PROJECTS):
    buildOne(name)

build(sys.argv[1:])

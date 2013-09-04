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

#DEFAULT_PROJECTS = 'command', 'slow', 'tests', 'support'
DEFAULT_PROJECTS = 'slow',
SEPARATE_OUT_FILE = False

def buildOne(name):
  base = name.split('.')[0]
  doc = '/development/rec/projects/%s/%s.jucer' % (base, name)
  if SEPARATE_OUT_FILE:
    out_doc = '/development/rec/projects/%s/%s.out.jucer' % (base, name)
  else:
    out_doc = doc


  results = jucer.JucerDomFile(doc, 'test' in name, '/development').toxml()
  f = open(out_doc, 'w')
  for line in results.split('\n'):
    if line.strip():
      f.write(line)
      f.write('\n')
  print 'Written', out_doc

def build(names):
  for name in (names or DEFAULT_PROJECTS):
    buildOne(name)

build(sys.argv[1:])

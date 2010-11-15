#!/usr/local/bin/python
#
# Handle .jucer files!
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
#
# Essentially, you can do as you please with it.  Have fun!

import os

import jucer


LIBRARIES = (
  dict(header='rec/src', header_only=True),
  dict(header='rec/genfiles/proto', header_only=True),
  dict(header='juce', header_only=True),
  dict(header='rec/src/rec/data/yaml/include', header_only=True),

  dict(name='libcddb', libraries=['cddb']),
  dict(name='gflags'),
  dict(name='glog', win_header='glog/src/windows'),
  dict(name='gtest', libraries=['gtest', 'gtest_main']),
  dict(name='iconv', header_needed=False, system=True),

  dict(name='mpg123',
       include='',
       win_header='mpg123/ports/MSVC++',
       win_extralinkpath=r'\ports\MSVC++\2008'),
  dict(name='protobuf', win_extralinkpath=r'\vsprojects',
       win_header='../../../../../protobuf/src'),

  dict(name='MSVCRTD', win_nodefaultlib=True),
  dict(name='msvcprtd', win_nodefaultlib=True),

  dict(name='../..', header_only=True, relative=False),
)


def build(*names):
  for name in names:
    root = os.getenv('ROOT')
    base = name.split('.')[0]
    doc = '%s/rec/projects/%s/%s.jucer' % (root, base, name)
    if '.win' in name:
      plat = 'win'
    else:
      plat = 'mac'

    results = jucer.Jucer(doc, 'test' in name, LIBRARIES, root, plat).toxml()
    f = open(doc, 'w')
    for line in results.split('\n'):
      if line.strip():
        f.write(line)
        f.write('\n')
    print 'Written', doc


build('slow.mac', 'slow.win', 'tests')

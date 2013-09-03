#!/usr/local/bin/python

# Build a structure representing a .jucer file, and modify it.
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
#
# Essentially, you can do as you please with it.  Have fun!

import dom_file
import filetree
import os.path

FILE_GROUPS = [
  ('src', 'src/rec'),
  ('genfiles', 'genfiles/proto'),
  ('art', 'projects/slow/art'),
  ('text', 'projects/slow/text'),
]

FILE_GROUPS = [
  ('src', 'rec'),
  ('genfiles', 'proto'),
  ('art', 'projects/slow/art'),
  ('text', 'projects/slow/text'),
]

SUFFIXES = set([
  'c',
  'cc',
  'cpp',
  'def',
  'h',
  'png',
  'svg',
  ])

COMPILE_SUFFIXES = set(['.c', '.cc', '.cpp'])

class JucerDomFile(object):
  def __init__(self, filename, is_test, root):
    self.dom_file = dom_file.DomFile(filename)
    self.create = self.dom_file.create
    self.is_test = is_test
    self.root = root

  def toxml(self):
    self.set_maingroup()
    return self.dom_file.dom.toprettyxml()

  def set_maingroup(self):
    old = self.dom_file.element('MAINGROUP')
    maingroup_name = old.getAttribute('name')
    self.dom_file.compute_dict(old)
    maingroup = self.create('MAINGROUP', maingroup_name, name=maingroup_name)
    self.dom_file.documentElement.replaceChild(maingroup, old)

    root = '%s/rec' % self.root
    for file_group, name in (FILE_GROUPS):
      tree_name = '%s/%s/%s' % (root, file_group, name)
      tree = filetree.filetree(tree_name, self.accept_cpp)
      if tree:
        maingroup.appendChild(self.create_file_or_group(file_group, name, tree,
                                                        maingroup_name))
      else:
        print 'ERROR: no file for %s' % tree_name

    maingroup.appendChild(self.create_file('Main.cpp', 'Main.cpp',
                                           maingroup_name + '/Main.cpp'))

  def create_file_or_group(self, prefix, name, tree, path):
    if type(tree) is str:
      return self.create_file(name, '../../%s/%s' % (prefix, name), path)
    else:
      group = self.create('GROUP', path, name=name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      new_path = path + '/' + name
      for k, v in tree.iteritems():
        group.appendChild(self.create_file_or_group(prefix, k, v, new_path))

      return group

  def create_file(self, name, file, path):
    isPNG = file.endswith('.png')
    compile = any(file.endswith(s) for s in COMPILE_SUFFIXES)
    resource = not compile and (not file.endswith('.h'))
    d = dict(name=name, resource=str(int(resource)), file=file,
             compile=str(int(compile)))
    return self.create('FILE', path, **d)

  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))

  def accept_cpp(self, s):
    r = (self.accept(s) and
            ('.' + s).split('.')[-1] in SUFFIXES and
            not (self.is_test and 'Main.c' in s) and
            'mfMath.h' not in s)
    # print "accept_cpp", s, r
    return r
  # TODO: is that second-last condition now irrelevant?

  def accept(self, s):
    return s and (self.is_test or not '_test.' in s)

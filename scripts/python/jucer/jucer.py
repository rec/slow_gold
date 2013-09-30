from __future__ import print_function

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
  ('src', 'rec'),
  ('genfiles', 'proto'),
  ('art', 'projects/slow/art'),
  ('text', 'projects/slow/text'),
]

FILE_GROUPS = [
  ('src', 'src/rec'),
  ('genfiles', 'genfiles/proto'),
  ('art', 'projects/slow/art'),
  ('text', 'projects/slow/text'),
]

SUFFIXES = set([
  'c',
  'cc',
  'cpp',
  'def',
  'h',
  'layout',
  'png',
  'svg',
  ])

OMITTED_SUFFIXES = set(['.py', '.proto'])

ACCEPT_ALL_SUFFIXES = False

def accept_suffix(filename):
  suffix = ('.' + filename).split('.')[-1]

  return (suffix not in OMITTED_SUFFIXES) and (
    ACCEPT_ALL_SUFFIXES or suffix in SUFFIXES)


COMPILE_SUFFIXES = set(['.c', '.cc', '.cpp'])

class JucerDomFile(dom_file.DomFile):
  def __init__(self, filename, is_test, root):
    super(JucerDomFile, self).__init__(filename)
    self.is_test = is_test
    self.root = root

  def toxml(self):
    self.set_maingroup()
    return self.dom.toprettyxml()

  def set_maingroup(self):
    old_maingroup = self.element('MAINGROUP')
    maingroup_name = old_maingroup.getAttribute('name')
    self.compute_dict(old_maingroup)
    maingroup = self.create('MAINGROUP', maingroup_name, name=maingroup_name)
    self.documentElement.replaceChild(maingroup, old_maingroup)

    root = '%s/rec' % self.root
    for group, path in FILE_GROUPS:
      tree_name = '%s/%s' % (root, path)
      tree = filetree.filetree(tree_name, self.accept)
      if tree:
        child = self.create_file_or_group(
          group, path, tree, maingroup_name, group)
        maingroup.appendChild(child)
      else:
        print('ERROR: no file for %s' % tree_name)

    maingroup.appendChild(self.create_file('Main.cpp', 'Main.cpp',
                                           maingroup_name + '/Main.cpp'))

  def create_file_or_group(self, prefix, name, tree, path, groupname=''):
    if type(tree) is str:
      return self.create_file(name, tree, path)
    else:
      group = self.create('GROUP', path, name=groupname or name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      new_path = os.path.join(path, name)
      for k, v in tree.iteritems():
        group.appendChild(self.create_file_or_group(prefix, k, v, new_path))

      return group

  def create_file(self, name, filename, path):
    compile = any(filename.endswith(s) for s in COMPILE_SUFFIXES)
    resource = not compile and (not filename.endswith('.h'))
    return self.create('FILE', path,
                       name=name,
                       file=filename,
                       resource='01'[resource],
                       compile='01'[compile])

  def accept(self, s):
    return (
      s and
      (self.is_test or not '_test.' in s) and
      accept_suffix(s) and
      not (self.is_test and 'Main.c' in s))

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

RANDOMIZE_IDS = not True

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

class JucerDomFile(dom_file.DomFile):
  def __init__(self, filename, is_test, root):
    dom_file.DomFile.__init__(self, filename)
    self.is_test = is_test
    self.root = root
    self.file_id_dict = {}

  def toxml(self):
    self.set_maingroup()
    return self.dom.toprettyxml()

  def set_maingroup(self):
    old = self.element('MAINGROUP')
    name = old.getAttribute('name')
    self.set_file_id_dict(old, '')

    maingroup = self.create_from_dict('MAINGROUP', name, name=name)
    self.documentElement.replaceChild(maingroup, old)

    for prefix, n2 in (FILE_GROUPS):
      self.create_top_level_group(maingroup, prefix, n2, '%s/rec' % self.root, name)

    maingroup.appendChild(self.create_file('Main.cpp', 'Main.cpp',
                                          name + '/Main.cpp'))

  def create_top_level_group(self, parent, prefix, name, root, path):
    tree_name = '%s/%s/%s' % (root, prefix, name)
    tree = filetree.filetree(tree_name, self.accept_cpp)
    if tree:
      parent.appendChild(self.create_file_or_group(prefix, name, tree, path))
    else:
      print 'ERROR: no file for %s' % tree_name

  def set_file_id_dict(self, n, path, depth=0):
    if path:
      path += '/'
    path += n.getAttribute('name')

    self.file_id_dict[path] = n.getAttribute('id')
    for g in n.childNodes:
      if hasattr(g, 'tagName') and g.tagName in ['GROUP', 'FILE']:
        self.set_file_id_dict(g, path, depth + 1)

  def create_from_dict(self, xmlName, path, **attributes):
    if RANDOMIZE_IDS:
      id = dom_file.randomId()
    else:
      id = self.file_id_dict.get(path + '/' + attributes['name'], None)
    if id:
      attributes.update(id=id)
    return self.create(xmlName, **attributes)

  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))

  def create_file(self, name, file, path):
    isPNG = file.endswith('.png')
    compile = str(int(not (file.endswith('.h') or isPNG)))
    resource = str(int(isPNG))
    d = dict(name=name, resource=resource, file=file, compile=compile)
    return self.create_from_dict('FILE', path, **d)

  def create_file_or_group(self, prefix, name, tree, path):
    if type(tree) is str:
      return self.create_file(name, '../../%s/%s' % (prefix, name), path)
    else:
      group = self.create_from_dict('GROUP', path, name=name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      new_path = path + '/' + name
      for k, v in tree.iteritems():
        group.appendChild(self.create_file_or_group(prefix, k, v, new_path))

      return group

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

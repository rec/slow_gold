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


class Jucer(dom_file.DomFile):
  def __init__(self, filename, is_test, root):
    dom_file.DomFile.__init__(self, filename)
    self.is_test = is_test
    self.root = root
    self.file_id_dict = {}


  def toxml(self):
    self.setMaingroup()
    return self.dom.toprettyxml()


  def setFileIdDict(self, n, path, depth=0):
    if path:
      path += '/'
    path += n.getAttribute('name')

    self.file_id_dict[path] = n.getAttribute('id')
    for g in n.childNodes:
      if hasattr(g, 'tagName') and g.tagName in ['GROUP', 'FILE']:
        self.setFileIdDict(g, path, depth + 1)


  def createFromDict(self, xmlName, path, **attributes):
    id = self.file_id_dict.get(path + '/' + attributes['name'], None)
    if id:
      attributes.update(id=id)
    return self.create(xmlName, **attributes)


  def setMaingroup(self):
    old = self.element('MAINGROUP')
    name = old.getAttribute('name')
    self.setFileIdDict(old, '')

    maingroup = self.createFromDict('MAINGROUP', name, name=name)
    self.documentElement.replaceChild(maingroup, old)

    for prefix, n2 in (('src', 'rec'), ('genfiles', 'proto')):
      self.createCPPFileGroup(maingroup, prefix, n2, '%s/rec' % self.root, name)
    maingroup.appendChild(self.createFile('Main.cpp', 'Main.cpp',
                                          name + '/Main.cpp'))


  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))


  def createCPPFileGroup(self, parent, prefix, name, root, path):
    tree = filetree.filetree('%s/%s/%s' % (root, prefix, name), self.acceptCpp)
    parent.appendChild(self.createFileOrGroup(prefix, name, tree, path))


  def createFile(self, name, file, path):
    return self.createFromDict('FILE',
                               path,
                               name=name,
                               resource='0',
                               file=file,
                               compile=str(int(not file.endswith('.h'))))


  def createFileOrGroup(self, prefix, name, tree, path):
    if type(tree) is str:
      return self.createFile(name, '../../%s/%s' % (prefix, name), path)

    else:
      group = self.createFromDict('GROUP', path, name=name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      new_path = path + '/' + name
      for k, v in tree.iteritems():
        group.appendChild(self.createFileOrGroup(prefix, k, v, new_path))

      return group


  def acceptCpp(self, s):
    return (self.accept(s) and
            ('.' + s).split('.')[-1] in ['h', 'cpp', 'cc', 'c'] and
            not (self.is_test and 'Main.c' in s))
  # TODO: is that last condition now irrelevant?


  def accept(self, s):
    return s and (self.is_test or not '_test.' in s)

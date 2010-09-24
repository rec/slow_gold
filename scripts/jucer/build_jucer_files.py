#!/usr/local/bin/python

import os

import dom_file
import filetree
import libraries
import odict

ROOT = os.getenv('ROOT')


class Jucer(dom_file.DomFile):
  JUCE_ROOT = '../../../../..'
  LIBRARY_ROOT = JUCE_ROOT + '/build/mac'
  CHARS = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
  ID_SIZE = 9

  def __init__(self, filename, is_test):
    dom_file.DomFile.__init__(self, filename)
    self.is_test = is_test


  def toxml(self):
    self.setLibraries()
    self.setHeaders()
    self.setMaingroup()
    return self.dom.toprettyxml()


  def setLibraries(self, config='debug'):
    xcode = self.element('EXPORTFORMATS', 'XCODE_MAC')
    libs = self.join(libraries.LIBRARIES.getLinks(Jucer.LIBRARY_ROOT, config))
    xcode.setAttribute('extraLinkerFlags', libs)


  def setHeaders(self):
    configurations = self.element('CONFIGURATIONS')
    for c in configurations.getElementsByTagName('CONFIGURATION'):
      config = c.getAttribute('name').lower()
      headerPath = self.join(libraries.LIBRARIES.getHeaders(
          Jucer.JUCE_ROOT, 'build/mac/%s' % config), ';')
      c.setAttribute('headerPath', headerPath)


  def setMaingroup(self):
    old = self.element('MAINGROUP')
    maingroup = self.create('MAINGROUP', name=old.getAttribute('name'))
    self.documentElement.replaceChild(maingroup, old)

    for prefix, name in (('', 'src'),
                         ('genfiles', 'proto')):
      self.createCPPFileGroup(maingroup, prefix, name, '%s/rec' % ROOT)
    maingroup.appendChild(self.createFile('Main.cpp', 'Main.cpp'))


  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))


  def createCPPFileGroup(self, parent, prefix, name, root):
    tree = filetree.filetree('%s/%s/%s' % (root, prefix, name), self.acceptCpp)
    parent.appendChild(self.createFileOrGroup(prefix, name, tree))


  def createFile(self, name, file):
    return self.create('FILE',
                       name=name,
                       resource='0',
                       file=file,
                       compile=str(int(not file.endswith('.h'))))


  def createFileOrGroup(self, prefix, name, tree):
    if type(tree) is str:
      return self.createFile(name, '../../%s/%s' % (prefix, name))

    else:
      group = self.create('GROUP', name=name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      for k, v in tree.iteritems():
        group.appendChild(self.createFileOrGroup(prefix, k, v))

      return group


  def acceptCpp(self, s):
    return (self.accept(s) and
            ('.' + s).split('.')[-1] in ['h', 'cpp', 'cc', 'c'] and
            not (self.is_test and 'Main.c' in s))


  def accept(self, s):
    return self.is_test or not 'test' in s


def overwrite(*names):
  for name in names:
    doc = '%s/rec/projects/%s/%s.jucer' % (ROOT, name, name)
    results = Jucer(doc, 'test' in name).toxml()
    open(doc, 'w').write(results)
    print 'Written', doc


overwrite('console', 'slow', 'tests')

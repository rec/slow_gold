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


  def setLibraries(self):
    xcode = self.element('EXPORTFORMATS', 'XCODE_MAC')
    xcode.setAttribute('extraLinkerFlags', self.get_libraries())


  def setHeaders(self):
    configurations = self.element('CONFIGURATIONS')
    for c in configurations.getElementsByTagName('CONFIGURATION'):
      config = c.getAttribute('name').lower()
      c.setAttribute('headerPath', self.get_headers(config))

  def setMaingroup(self):
    old = self.element('MAINGROUP')
    maingroup = self.create('MAINGROUP', name=old.getAttribute('name'))
    self.documentElement.replaceChild(maingroup, old)

    # Discard MAINGROUP and replace it with our directory trees.
    for prefix, name in (('', 'src'),
                         ('genfiles', 'proto')):
      self.create_cpp_file_group(maingroup, prefix, name, '%s/rec' % ROOT)


  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))


  def get_libraries(self, config='debug'):
    return self.join(lib.link(Jucer.LIBRARY_ROOT, config)
                     for lib in libraries.LIBRARIES)


  def get_headers(self, config):
    hdrs = ['rec/src', 'rec/genfiles/proto', 'juce'] + [
      lib.header('build/mac', config) for lib in libraries.LIBRARIES]
    hdrs = ['%s/%s' % (Jucer.JUCE_ROOT, h) for h in hdrs if h]
    return self.join(hdrs + ['../..'], ';')


  def create_cpp_file_group(self, parent, prefix, name, root):
    tree = filetree.filetree('%s/%s/%s' % (root, prefix, name), self.accept_cpp)
    parent.appendChild(self.create_file_group(prefix, name, tree))


  def create_file_group(self, prefix, name, tree):
    if type(tree) is str:
      # print "prefix", prefix, "name", name
      return self.create('FILE',
                         name=name,
                         resource='0',
                         file='../../%s/%s' % (prefix, name),
                         compile=str(int(not tree.endswith('.h'))))
    else:
      group = self.create('GROUP', name=name)
      if prefix:
        prefix = '%s/%s' % (prefix, name)
      else:
        prefix = name

      for k, v in tree.iteritems():
        group.appendChild(self.create_file_group(prefix, k, v))

      return group


  def accept_cpp(self, s):
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


overwrite('slow', 'tests')

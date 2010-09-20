#!/usr/local/bin/python

import os
import random
import stat
import sys
import xml.dom.minidom

import odict

class Library:
  def __init__(self, name, include='/include', libraries=None, system=False):
    self.name = name
    self.include = include
    self.system = system
    self.libraries = libraries or [name]

  def link(self, root, config):
    libraries = ['-l%s' % lib for lib in self.libraries]
    if not self.system:
      libraries.insert(0, '-L%s/%s/%s/lib' % (root, config, self.name))
    return ' '.join(libraries)

  def header(self, root, config):
    if self.system:
      return ''
    else:
      return '%s/%s/%s%s' % (root, config, self.name, self.include)


LIBRARIES = (
  Library('libcddb', libraries=['cddb']),
  Library('gflags'),
  Library('glog'),
  Library('gtest', libraries=['gtest', 'gtest_main']),
  Library('iconv', system=True),
  Library('mpg123', include=''),
  Library('protobuf'),
)

ROOT = os.getenv('ROOT')


class Jucer:
  JUCE_ROOT = '../../../../..'
  LIBRARY_ROOT = JUCE_ROOT + '/build/mac'
  CHARS = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
  ID_SIZE = 9

  def __init__(self, filename, is_test):
    self.dom = xml.dom.minidom.parse(open(filename))
    self.documentElement = self.dom.documentElement
    self.is_test = is_test


  def join(self, files, joiner=' '):
    return joiner.join(filter(self.accept, files))


  def get_libraries(self, config='debug'):
    return self.join(lib.link(Jucer.LIBRARY_ROOT, config) for lib in LIBRARIES)


  def get_headers(self, config):
    hdrs = ['rec/src', 'rec/genfiles/proto', 'juce'] + [
      lib.header('build/mac', config) for lib in LIBRARIES]
    hdrs = ['%s/%s' % (Jucer.JUCE_ROOT, h) for h in hdrs if h]
    return self.join(hdrs + ['../..'], ';')


  def toxml(self):
    xcode = self.element('EXPORTFORMATS', 'XCODE_MAC')
    xcode.setAttribute('extraLinkerFlags', self.get_libraries())

    configurations = self.element('CONFIGURATIONS')
    for c in configurations.getElementsByTagName('CONFIGURATION'):
      config = c.getAttribute('name').lower()
      c.setAttribute('headerPath', self.get_headers(config))

    old = self.element('MAINGROUP')
    maingroup = self.create('MAINGROUP', name=old.getAttribute('name'))
    self.documentElement.replaceChild(maingroup, old)

    # Discard MAINGROUP and replace it with our directory trees.
    for prefix, name in (('', 'src'),
                         ('genfiles', 'proto')):
      self.create_cpp_file_group(maingroup, prefix, name, '%s/rec' % ROOT)

    return self.dom.toprettyxml()


  def create(self, xml_name, **attributes):
    element = self.dom.createElement(xml_name)

    id = ''.join(random.choice(Jucer.CHARS) for i in xrange(Jucer.ID_SIZE))
    element.setAttribute('id', id)

    for k, v in attributes.iteritems():
      element.setAttribute(k, v)
    return element


  def create_cpp_file_group(self, parent, prefix, name, root):
    tree = self.get_cpp_file_tree('%s/%s/%s' % (root, prefix, name))
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
            not (self.is_test and 'Main.' in s))

  def accept(self, s):
    return self.is_test or not 'test' in s

  def element(self, *names):
    node = self.documentElement
    for n in names:
      node = node.getElementsByTagName(n)[0]
    return node


  def get_cpp_file_tree(self, file):
    try:
      st_mode = os.lstat(file).st_mode
    except OSError:
      print 'os.error', file
      return

    if stat.S_ISDIR(st_mode):
      values = odict.OrderedDict()
      for name in os.listdir(file):
        tree = self.get_cpp_file_tree(os.path.join(file, name))
        if tree:
          values[name] = tree

      return values

    elif stat.S_ISREG(st_mode):
      if self.accept_cpp(file):
        return file


def overwrite(*names):
  for name in names:
    doc = '%s/rec/projects/%s/%s.jucer' % (ROOT, name, name)
    results = Jucer(doc, 'test' in name).toxml()
    open(doc, 'w').write(results)
    print 'Written', doc


overwrite('slow', 'tests')

#!/usr/local/bin/python

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

#!/usr/local/bin/python

class Library:
  def __init__(self, name, **kwds):
    self.name = name
    self.kwds = kwds


  def get(self, **kwds):
    for k, v in kwds.iteritems():
      return self.kwds.get(k, v)

  def link(self, root, build):
    if self.get(header_only=False):
      return False

    libraries = ['-l%s' % lib for lib in self.get(libraries=[self.name])]
    if not self.get(system=False):
      libraries.insert(0, '-L%s/%s/%s/lib' % (root, build, self.name))

    return ' '.join(libraries)


  def header(self, root, build):
    if not self.get(header_needed=True):
      return ''

    elif self.get(absolute=False):
      return self.name

    elif self.get(header_only=False):
      return '%s/%s' % (root, self.name)

    else:
      return '%s/%s/%s%s' % (root, build, self.name,
                             self.get(include='/include'))


class Libraries:
  def __init__(self, *libraries):
    self.libraries = libraries


  def getHeaders(self, root, build):
    return filter(None, (i.header(root, build) for i in self.libraries))


  def getLinks(self, root, build):
    return filter(None, (i.link(root, build) for i in self.libraries))


LIBRARIES = Libraries(
  Library('rec/src', header_only=True),
  Library('rec/genfiles/proto', header_only=True),
  Library('juce', header_only=True),

  Library('libcddb', libraries=['cddb']),
  Library('gflags'),
  Library('glog'),
  Library('gtest', libraries=['gtest', 'gtest_main']),
  Library('iconv', header_needed=False),
  Library('mpg123', include=''),
  Library('protobuf'),

  Library('../..', header_only=True, absolute=True),
)

#!/usr/bin/python

import os
import sys


ROOT = '/Users/tom/Documents/development/rec/scripts/new/templates/'

GROUPS = {
  'h': dict(files=['.h']),
  'class': dict(files=['.cpp', '.h']),
  'test': dict(files=['.cpp', '.h', '_test.cpp']),
  'svg': dict(files=['.data.h', '.data.cpp'],
              filetype='svg',
              datatype='juce::Drawable'),
  'xml': dict(files=['.data.h', '.data.cpp'],
              filetype='xml',
              datatype='juce::XmlElement'),
  }

USAGE = """\
Usage:

  new <type> <filename>

where
  <type> is one of %s
  <filename> is a path to the new file name base

""" % ', '.join(GROUPS.keys())


def usageError(fail=True):
  if fail:
    print USAGE
    raise ValueError

def splitLargeLines(lines, lineLength=78, maxLineLength=16380):
  for i, l in enumerate(lines):
    while len(l) > lineLength:
      loc = maxSplit(l)
      if loc is -1:
        break
      yield l[0 : loc + 1] + '"\n  "'
      l = l[loc + 1 : ]

    if len(l) > maxLineLength:
      raise ValueError, "Couldn't split line %d, len %d" % (i, l)

    yield l + '\n'

def convertToCCode(data):
  data = '"%s\\n"' % (data.replace('"', '\\"') .replace('\n', '\\n"\n  "'))
  return ''.join(splitLargeLines(data.split('\n')))

def readDataFile(f):
  return convertToCCode(open(f).read())

def write(name, template, **context):
  with open(name, 'w') as out:
    out.write(template.format(**context))


def makeContext(group, path, classname, suffix):
  context = {}
  if group.has_key('datatype'):
    ft = group['filetype']
    suffix = suffix.replace('.data.', '.%s.' % ft)
    f = '/'.join(['rec', 'data', ft] + path + [classname + '.' + ft])
    context.update(data=readDataFile(f), datatype=group['datatype'])

  return dict(
    classname=classname,
    guard='__%s__' % '_'.join(s.upper() for s in path + [classname]),
    header_file='/'.join(path + [classname + suffix]),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    package='.'.join(path),
    **context)

def new(groupname, file):
  group = GROUPS.get(groupname, None)
  usageError(not group)

  name = os.path.abspath(file)
  path = ['rec'] + name.split('/src/rec/')[1].split('/')
  classname = path.pop()

  for suffix in group['files']:
    context = makeContext(group, path, classname, suffix)
    write(file + suffix, open(ROOT + suffix).read(), **context)


if __name__ == "__main__":
  args = sys.argv[1:]
  usageError(len(args) is not 2)
  new(*args)

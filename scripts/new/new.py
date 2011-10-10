#!/usr/bin/python

import os
import sys

import split

ROOT = '/Users/tom/Documents/development/rec/scripts/new/templates/'

GROUPS = {
  'h': dict(files=['.h']),
  'class': dict(files=['.cpp', '.h']),
  'cpp': dict(files=['.cpp']),
  'test': dict(files=['.cpp', '.h', '_test.cpp']),
  'svg': dict(files=['.data.h', '.data.cpp'],
              filetype='svg',
              datatype='juce::Drawable'),
  'xml': dict(files=['.data.h', '.data.cpp'],
              filetype='xml',
              datatype='juce::XmlElement'),
  }

USAGE = """\
new.py creates new C++ files from templates.

You select which type of C++ files you want to create - your current choices are
   h, class, cpp, test, svg and xml.

Usage:

  new <type> <filename>

where
  <type> is one of %s
  <filename> is a path to the new file name base

""" % ', '.join(GROUPS)


def usageError(success=False, error=None, usage=USAGE):
  if not success:
    if error:
      print 'ERROR: ', error
    print usage
    raise ValueError

def convertToCCode(data):
  data = '"%s\\n"' % (data.replace(chr(13), '').
                      replace('"', '\\"').
                      replace('\n', '\\n"\n  "'))
  return ''.join(split.splitLargeLines(data.split('\n')))

def write(name, template, **context):
  with open(name, 'w') as out:
    out.write(template.format(**context))

def makeContext(group, path, classname, file, suffix):
  context = {}

  return dict(
    classname=classname,
    guard='__%s__' % '_'.join(s.upper() for s in path + [classname]),
    header_file='/'.join(path + [classname + hsuffix]),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    package='.'.join(path),
    **context)

def createCppFiles(file, groupname):
  group = GROUPS.get(groupname, None)
  usageError(group, 'No group ' + groupname)

  name = os.path.abspath(file)
  path = ['rec'] + name.split('/src/rec/')[1].split('/')
  classname = path.pop()
  context = dict(
    classname=classname,
    guard='__%s__' % '_'.join(s.upper() for s in path + [classname]),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    package='.'.join(path))

  if group.has_key('datatype'):
    ft = group['filetype']
    datafile = '%s.%s' % (file, ft)
    data = convertToCCode(open(datafile).read())
    context.update(data=data, datatype=group['datatype'])
    headerfile = '%s.%s.h' % (classname, ft)
  else:
    headerfile = classname + '.h'
    ft = ''

  context.update(header_file = '/'.join(path + [headerfile]))
  for suffix in group['files']:
    wsuffix = suffix.replace('.data.', '.%s.' % ft)
    with open(file + wsuffix, 'w') as out:
      template = open(ROOT + suffix).read()
      out.write(template.format(**context))


if __name__ == "__main__":
  args = sys.argv[1:]

  while args:
    arg = args.pop(0).split('.')
    if len(arg) > 1:
      createCppFiles('.'.join(arg[0 : -1]), arg[-1])
    else:
      usageError(args)  # Need at least one more argument
      createCppFiles(arg, args.pop(0))

#!/usr/bin/python

import getopt
import os
import sys

import split

ROOT = '/Users/tom/Documents/development/rec/scripts/new/templates/'

GROUPS = {
  'h': dict(files=['.h']),
  'class': dict(files=['.cpp', '.h']),
  'cpp': dict(files=['.cpp']),
  'def': dict(files=['.def.h', '.def.cpp'],
              filetype='def',
              datatype='def'),
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
   h, class, cpp, def, test, svg and xml.

Usage:

  new [--proto=<protoname>] <type> <filename>

where
  <type> is one of %s
  <filename> is a path to the new file name base
  --proto indicates the protocol buffer type and is a required argument
    only if the type is 'def'
  --namespace is an optional namespace, separated by dots - otherwise, the
    namespace is computed automatically

""" % ', '.join(GROUPS)


def usageError(success=False, error=None, usage=USAGE):
  if not success:
    if error:
      print
      print 'ERROR: ', error
      print
    print usage
    raise ValueError

def convertToCCode(data, convertNewLines=True):
  nl = convertNewLines and '\\n"\n  "' or ' "\n"'
  end = convertNewLines and '\n' or ' '
  data = '"%s%s"' % (data.replace(chr(13), '').
                      replace('"', '\\"').
                      replace('\n', nl), end)
  res = ''.join(split.splitLargeLines(data.split('\n')))
  if not (convertNewLines or res[-1].isspace()):
    res += ' '

  return res

def write(name, template, **context):
  with open(name, 'w') as out:
    out.write(template.format(**context))

def createCppFiles(file, groupname, protoname, namespace, includes):
  group = GROUPS.get(groupname, None)
  usageError(group, 'No group ' + groupname)

  name = os.path.abspath(file)
  path = name.split('/src/')[1].split('/')
  classname = path.pop()

  if namespace:
    path = namespace.split('.')

  if not path or path[0] != 'rec':
    path.insert(0, 'rec')

  context = dict(
    classname=classname,
    commandline=' '.join(['new'] + sys.argv[1:]),
    guard='__%s__' % '_'.join(s.upper() for s in path + [classname]),
    includes='\n'.join(includes),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    package='.'.join(path),
    protoname=protoname)

  if group.has_key('datatype'):
    datatype = group['datatype']
    isDef = (datatype == 'def')
    if isDef:
      usageError(protoname, 'No --proto flag set')
      context['classname'] = classname[0].lower() + classname[1:]

    ft = group['filetype']
    datafile = '%s.%s' % (file, ft)
    data = convertToCCode(open(datafile).read(), not isDef)
    context.update(data=data, datatype=datatype)
    headerfile = '%s.%s.h' % (classname, ft)
  else:
    headerfile = classname + '.h'
    ft = ''

  context.update(header_file = '/'.join(path + [headerfile]))
  for suffix in group['files']:
    wsuffix = suffix.replace('.data.', '.%s.' % ft)
    fullFile = file + wsuffix
    with open(fullFile, 'w') as out:
      template = open(ROOT + suffix).read()
      out.write(template.format(**context))
    print 'Written', fullFile

def parseArgs(args):
  optlist, args = getopt.getopt(args, 'p:',
                                ['proto=', 'namespace=', 'include='])
  protoname, namespace = None, None
  includes = []
  for name, value in optlist:
    if name == '-p' or name == '--proto':
      protoname = value

    elif name == '-n' or name == '--namespace':
      namespace = value

    elif name == '--include':
      value = value.split('/')
      if value[0] != 'rec':
        value.insert(0, 'rec')
      value = '/'.join(value)
      if not value.endswith('.h'):
        value += '.h'
      includes.append('#include "%s"' % value)

  while args:
    arg = args.pop(0).split('.')
    if len(arg) > 1:
      file = '.'.join(arg[0 : -1])
      createCppFiles(file, arg[-1], protoname, namespace, includes)
    else:
      usageError(args)  # Need at least one more argument
      createCppFiles(arg, args.pop(0), protoname)

if __name__ == "__main__":
  parseArgs(sys.argv[1:])

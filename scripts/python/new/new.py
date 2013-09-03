#!/usr/bin/python

import getopt
import os
import sys
import xml.dom.minidom

import split

USAGE_MESSAGE = """\
new.py creates new C++ files from templates.

You select which type of C++ files you want to create - your current choices are
   h, class, cpp, def, test, svg and xml.

Usage:

  new [--proto=<protoname>] [--namespace=rec.foo.bar] <type> <filename>

where
  <type> is one of %s
  <filename> is a path to the new file name base
  --proto indicates the protocol buffer type and is a required argument
    only if the type is 'def'
  --namespace is an optional namespace, separated by dots - otherwise, the
    namespace is computed automatically

"""

ROOT = '/development/rec/scripts/new/templates/'

def cleanSvg(data):
  tagNames = set(['metadata', 'i:pgf'])

  def removeTags(node):
    if hasattr(node, 'childNodes'):
      for n in node.childNodes:
        if n.nodeName in tagNames:
          node.removeChild(n)
        else:
          removeTags(n)

  document = xml.dom.minidom.parseString(data)
  removeTags(document)
  return document.toprettyxml('  ')


GROUPS = {
  'h': dict(files=['.h']),
  'class': dict(files=['.cpp', '.h']),
  'cpp': dict(files=['.cpp']),
  'def': dict(files=['.def.h', '.def.cpp'],
              filetype='def',
              datatype='def'),
  'test': dict(files=['.cpp', '.h', '_test.cpp']),
  'svg': dict(files=['.svg.h', '.svg.cpp'],
              filetype='svg',
              datatype='juce::Drawable',
              process=cleanSvg),
  'xml': dict(files=['.data.h', '.data.cpp'],
              filetype='xml',
              datatype='juce::XmlElement'),
}

USAGE = USAGE_MESSAGE % ', '.join(GROUPS)

MAX_LINES = 500

def usageError(success=False, error=None, usage=USAGE):
  if not success:
    if error:
      print
      print 'ERROR: ', error
      print
    print usage
    raise ValueError

def escapeInput(data):
  nl = '\\n"\n  "'
  return (data.replace(chr(13), '').
          replace('\\', '\\\\').
          replace('"', '\\"').
          replace('\n', nl))

def convertToCCode(data):
  data = '"%s "' % escapeInput(data)
  res = ''.join(split.splitLargeLines(data.split('\n')))
  if len(res) < 65536:
    return res + ' '

  r2 = res.split('\n')
  r3 = []
  while r2:
    r3.append('\n'.join(r2[0:MAX_LINES]))
    r2 = r2[MAX_LINES:]
  return 'string(' + ')\n + string('.join(r3) + ')'

def printRes(res):
  print "***\n***\n***\n***\n"
  for r in res:
    print '\n!'
    for s in r:
      print ' ', s,
  print "\n\n***\n***\n***\n***"


def convertToCCodeNew(data):
  data = '"%s "' % escapeInput(data)
  data = list(split.splitLargeLines(data.split('\n')))
  if len(data) <= MAX_LINES:
    return ''.join(data) + ' '
  else:
    res = []
    res2 = []
    while data:
      res.append(''.join(data[0:MAX_LINES]))
      res2.append(data[0:MAX_LINES])
      data = data[MAX_LINES:]
    print "***\n***\n***\n***\n"
    printRes(res2)
    print "***\n***\n***\n***\n"
    return 'string(' + '")\n + string("'.join(res) + ')'

def write(name, template, **context):
  with open(name, 'w') as out:
    out.write(template.format(**context))

def fixClassname(c):
  return c.replace('-', '')

def computePaths(file, namespace):
  name = os.path.abspath(file)
  splitPath = name.split('/src/')
  if len(splitPath) > 1:
    originalPath = splitPath[-1].split('/')
    classname = originalPath.pop()
    if namespace:
      path = namespace.split('.')
    else:
      path = originalPath

  elif not namespace:
    raise Exception('Must specify a namespace if not in source tree')

  else:
    path = namespace.split('.')
    originalPath = path
    classname = name.split('/')[-1]

  if not path:
    path.insert(0, 'rec')

  return name, path, originalPath, classname

def createCppFiles(file, groupname, protoname, namespace, includes, output):
  group = GROUPS.get(groupname, None)
  usageError(group, 'No group ' + groupname)

  name, path, originalPath, classname = computePaths(file, namespace)
  context = dict(
    classname=fixClassname(classname),
    commandline=' '.join(['new'] + sys.argv[1:]),
    filename='%s.%s' % (os.path.split(name)[1], groupname),
    guard='__%s__' % '_'.join(s.upper() for s in path + [fixClassname(classname)]),
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
      context['classname'] = fixClassname(classname[0].lower() + classname[1:])

    ft = group['filetype']
    datafile = '%s.%s' % (file, ft)
    data = open(datafile).read()
    if group.has_key('process'):
      data = group['process'](data)
    data = convertToCCode(data)
    context.update(data=data, datatype=datatype)
    header_file = '%s.%s.h' % (classname, ft)
  else:
    header_file = classname + '.h'
    ft = ''

  context.update(header_file = '/'.join(originalPath + [header_file]))

  for suffix in group['files']:
    wsuffix = suffix.replace('.data.', '.%s.' % ft)
    outfile = file + wsuffix
    if output:
      outfile = output + '/' + outfile.split('/')[-1]
    with open(outfile, 'w') as out:
      template = open(ROOT + suffix).read()
      out.write(template.format(**context))
    print 'Written', output

def parseArgs(args):
  optlist, args = getopt.getopt(args, 'p:',
                                ['proto=', 'namespace=', 'include=', 'output=',
                                 'group='])
  protoname, namespace, output, group = None, None, None, None
  includes = []
  for name, value in optlist:
    if name == '-p' or name == '--proto':
      protoname = value

    elif name == '-n' or name == '--namespace':
      namespace = value

    elif name == '-o' or name == '--output':
      output = value

    elif name == '-g' or name == '--group':
      group = value

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
      group = group or arg[-1]
      createCppFiles(file, group, protoname, namespace, includes, output)
    else:
      usageError(args)  # Need at least one more argument
      createCppFiles(arg, group, args.pop(0), protoname)

if __name__ == "__main__":
  parseArgs(sys.argv[1:])
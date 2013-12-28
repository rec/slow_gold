#!/usr/bin/python

import getopt
import json
import os
import os.path
import sys

import split

USAGE_MESSAGE = """\
new.py creates new C++ files from templates.

You select which type of C++ files you want to create - your current choices are
   h, class, cpp, def, test, svg and xml.

Usage:

  new [--namespace=rec.foo.bar] <type> <filename>

where
  <type> is one of %s
  <filename> is a path to the new file name base
  --namespace is an optional namespace, separated by dots - otherwise, the
    namespace is computed automatically

"""

ROOT = os.path.join(os.path.dirname(__file__), 'templates')

GROUPS = {
  'h': dict(files=['.h']),
  'class': dict(files=['.cpp', '.h']),
  'cpp': dict(files=['.cpp']),
  'test': dict(files=['.cpp', '.h', '_test.cpp']),
}

USAGE = USAGE_MESSAGE % ', '.join(GROUPS)
CONFIG_FILE_NAME = 'config-new.json'

def usage_error(success=False, error=None, usage=USAGE):
  if not success:
    if error:
      print
      print 'ERROR: ', error
      print
    print usage
    raise ValueError

def write(name, template, **context):
  with open(name, 'w') as out:
    out.write(template.format(**context))

def fix_classname(c):
  return c.replace('-', '')

def compute_paths(fname, namespace, dirname):
  name = os.path.abspath(fname)
  path = os.path.relpath(fname, dirname)
  original_path = path.split('/')
  classname = original_path.pop()
  if namespace:
    path = namespace.split('.')
  else:
    path = original_path

  return name, path, original_path, classname

def create_cpp_files(
    fname, groupname, namespace, includes, output, dirname, config):
  group = GROUPS.get(groupname, None)
  usage_error(group, 'No group ' + groupname)

  name, path, original_path, classname = compute_paths(
    fname, namespace, dirname)
  context = dict(
    base_include=config['base_include'],
    classname=fix_classname(classname),
    commandline=' '.join(['new'] + sys.argv[1:]),
    filename='%s.%s' % (os.path.split(name)[1], groupname),
    guard='__%s__' % '_'.join(s.upper()
                              for s in path + [fix_classname(classname)]),
    includes='\n'.join(includes),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    package='.'.join(path))

  header_file = classname + '.h'
  ft = ''

  context.update(header_file = '/'.join(original_path + [header_file]))

  for suffix in group['files']:
    wsuffix = suffix.replace('.data.', '.%s.' % ft)
    outfile = fname + wsuffix
    if output:
      outfile = output + '/' + outfile.split('/')[-1]
    with open(outfile, 'w') as out:
      template = open(os.path.join(ROOT, suffix)).read()
      out.write(template.format(**context))
    print 'Written', outfile

def root_config():
  dirname = os.path.abspath(os.getcwd())
  while True:
    try:
      with open(os.path.join(dirname, CONFIG_FILE_NAME)) as f:
        return dirname, json.loads(f.read())
    except IOError:
      dirname, old = os.path.dirname(dirname), dirname
      if old == dirname:
        raise Exception('Didn\'t find config file %s' % CONFIG_FILE_NAME)

def parse_args(args):
  optlist, args = getopt.getopt(
    args, 'p:',
    ['namespace=', 'include=', 'output='])

  namespace, output = None, None
  includes = []
  for name, value in optlist:
    if name == '-n' or name == '--namespace':
      namespace = value

    elif name == '-o' or name == '--output':
      output = value

    elif name == '--include':
      value = value.split('/')
      if value[0] != 'rec':
        value.insert(0, 'rec')
      value = '/'.join(value)
      if not value.endswith('.h'):
        value += '.h'
      includes.append('#include "%s"' % value)

  dirname, config = root_config()
  while args:
    arg = args.pop(0).split('.')
    if len(arg) > 1:
      fname = '.'.join(arg[0 : -1])
      create_cpp_files(fname, arg[-1], namespace, includes, output, dirname, config)
    else:
      usage_error(error="Didn't understand %s" % arg)  # Need at least one more argument


if __name__ == "__main__":
  parse_args(sys.argv[1:])

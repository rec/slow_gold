#!/usr/bin/python

import optparse
import os
import sys

import split
import templates

# DEFAULT_SUFFIXES = ['_test.cpp', '.h', '.cpp']
DEFAULT_SUFFIXES = ['.h', '.cpp', '.proto']
SUFFIXES = ['.svg.h', '.svg.cpp', '_test.cpp', '.h', '.cpp']

def new_class(filename, **context):
  if not filename.startswith('/'):
    filename = os.getcwd() + '/' + filename

  path = filename.split('rec/src/')[-1].split('/')
  file_root = path.pop()

  method_body = ';'
  suffixes = DEFAULT_SUFFIXES

  if '.' in file_root:
    file_root, suffix = split.split_suffix(file_root, SUFFIXES)
    suffixes = [suffix]
    method_body = ' {\n  }'

  file_parts = filename.split('/')
  file_parts[-1] = file_root
  file_base = '/'.join(file_parts)

  if 'svg' in context:
    suffix = '.svg.h'
  else:
    suffix = '.h'

  context.update(
    classname=file_root,
    guard='__%s__' % '_'.join(s.upper() for s in path + [file_root]),
    header_file='/'.join(path + [file_root + suffix]),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    method='get',
    method_body=method_body,
    package='.'.join(path),
    )

  for suffix in suffixes:
    open(file_base + suffix, 'w').write(templates.TEMPLATES[suffix].format(**context))
    print 'Written %s%s' % (file_base, suffix)


def readSVGFile(f):
  svg = '"%s\\n"' % (open(f).read().replace('"', '\\"')
                     .replace('\n', '\\n"\n  "'))

  return ''.join(split.splitLargeLines(svg.split('\n')))


if __name__ == "__main__":
  context = dict(
    cmd=sys.argv[0].split('/')[-1],
    args=' '.join(sys.argv[1:]))

  parser = optparse.OptionParser()
  parser.add_option('--svg', dest='svg')

  options, files = parser.parse_args()
  if options.svg:
    context['svg'] = readSVGFile(options.svg)
    context['svg_file'] = options.svg
    file = (files or [options.svg.split('/')[-1]])[0].split('.')[0]
    files = [file + '.svg.cpp', file + '.svg.h']

  for f in files:
    new_class(f, **context)




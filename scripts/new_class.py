#!/usr/local/bin/python

import os
import optparse
import sys

DEFAULT_SUFFIXES = ['_test.cpp', '.h', '.cpp']
SUFFIXES = ['.svg.h', '.svg.cpp', '_test.cpp', '.h', '.cpp']


def split_suffix(filename):
  for s in SUFFIXES:
    if filename.endswith(s):
      return filename.split(s)[0], s


def new_class(filename, **context):
  if not filename.startswith('/'):
    filename = os.getcwd() + '/' + filename

  path = filename.split('rec/src/')[-1].split('/')
  file_root = path.pop()

  method_body = ';'
  suffixes = DEFAULT_SUFFIXES

  if '.' in file_root:
    file_root, suffix = split_suffix(file_root)
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
    header_file='/'.join(path + [file_root + suffix]),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    method='get',
    method_body=method_body,
    guard='__%s__' % '_'.join(s.upper() for s in path + [file_root]),
    )

  for suffix in suffixes:
    open(file_base + suffix, 'w').write(TEMPLATES[suffix].format(**context))
    print 'Written %s%s' % (file_base, suffix)


TEMPLATES = {
  '.svg.h':
"""#ifndef {guard}
#define {guard}

#include "JuceLibraryCode/JuceHeader.h"

{namespace}

struct {classname} {{
  static juce::Drawable* {method}();
}};

{namespace_end}

#endif  // {guard}
""",

  '.svg.cpp':
"""#include "{header_file}"
#include "rec/base/ArraySize.h"

{namespace}

using juce::Drawable;

// Original .svg file: {svg_file}

Drawable* {classname}::{method}() {{
  static const char data[] = {svg};

  static Drawable* d = Drawable::createFromImageData(data, arraysize(data));
  return d;
}};

{namespace_end}
""",

  '.h':
"""#ifndef {guard}
#define {guard}

#include "rec/base/base.h"

{namespace}

class {classname} {{
 public:
  {classname}() {{}}

  void {method}(){method_body}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY({classname});
}};

{namespace_end}

#endif  // {guard}
""",

  '.cpp':
"""#include "{header_file}"

{namespace}

void {classname}::{method}() {{
}}

{namespace_end}
""",


  '_test.cpp':
"""#include <gtest/gtest.h>
#include <glog/logging.h>

#include "{header_file}"

{namespace}
namespace {{

TEST({classname}, {method}) {{
}}

}}  // namespace
{namespace_end}
"""
}


def readSVGFile(f):
  return '"%s\\n"' % (open(f).read().replace('"', '\\"')
                      .replace('\n', '\\n"\n  "'))

if __name__ == "__main__":
  parser = optparse.OptionParser()
  parser.add_option('--svg', dest='svg')

  options, files = parser.parse_args()
  context = {}
  if options.svg:
    context['svg'] = readSVGFile(options.svg)
    context['svg_file'] = options.svg
    file = (files or [options.svg.split('/')[-1]])[0].split('.')[0]
    files = [file + '.svg.cpp', file + '.svg.h']

  for f in files:
    new_class(f, **context)




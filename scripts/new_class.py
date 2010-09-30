#!/usr/local/bin/python

import os
import sys


SUFFIXES = ['.h', '_test.cpp', '.cpp']

def split_suffix(filename):
  for s in SUFFIXES:
    if filename.endswith(s):
      return filename.split(s)[0], s


def new_class(filename):
  if not filename.startswith('/'):
    filename = os.getcwd() + '/' + filename

  path = filename.split('rec/src/')[-1].split('/')
  file_root = path.pop()

  if '.' in file_root:
    file_root, suffix = split_suffix(file_root)
    suffixes = [suffix]
    method_body = ' {\n  }'
  else:
    method_body = ';'
    suffixes = SUFFIXES
  file_parts = filename.split('/')
  file_parts[-1] = file_root
  file_base = '/'.join(file_parts)


  context = dict(
    classname=file_root,
    header_file='/'.join(path + [file_root + '.h']),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    method='someMethod',
    method_body=method_body,
    guard='__%s__' % '_'.join(s.upper() for s in path + [file_root]),
    )

  for suffix in suffixes:
    open(file_base + suffix, 'w').write(TEMPLATES[suffix].format(**context))
    print 'Written %s%s' % (file_base, suffix)

TEMPLATES = {
  '.h': """#ifndef {guard}
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
  '.cpp': """#include "{header_file}"

{namespace}

void {classname}::{method}() {{
}}

{namespace_end}
""",
  '_test.cpp': """#include <gtest/gtest.h>
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

if __name__ == "__main__":
  for f in sys.argv[1:]:
    new_class(f)

#!/usr/local/bin/python

import os
import sys

def new_class(filename):
  if not filename.startswith('/'):
    filename = os.getcwd() + '/' + filename

  path = filename.split('rec/src/')[-1].split('/')
  file_root = path.pop()

  if '.' in file_root:
    file_root, suffix = file_root.split('.')
    suffixes = [suffix]
    method_body = ' {\n  }'
  else:
    method_body = ';'
    suffixes = ['h', 'cpp']

  context = dict(
    classname=file_root,
    header_file='/'.join(path + [file_root + '.h']),
    namespace='\n'.join('namespace %s {' % p for p in path),
    namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
    method='someMethod',
    method_body=method_body,
    guard='__%s__' % '_'.join(s.upper() for s in path + [file_root]),
    )

  file_base = filename.split('.')[0] + '.'
  for suffix in suffixes:
    open(file_base + suffix, 'w').write(TEMPLATES[suffix].format(**context))
    print 'Written %s.%s' % (file_root, suffix)

TEMPLATES = dict(
  h="""#ifndef {guard}
#define {guard}

#include "rec/base/basictypes.h"

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
  cpp= """#include "{header_file}"

{namespace}

void {classname}::{method}() {{
}}

{namespace_end}
""")

if __name__ == "__main__":
  for f in sys.argv[1:]:
    new_class(f)

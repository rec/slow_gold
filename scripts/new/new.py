#!/usr/bin/python

import os

import args
import split
import groups

def new(files, context):
  for file, suffix in files:
    name = os.path.abspath(file)
    path = ['rec'] + name.split('/src/rec/')[1].split('/')
    classname = path.pop()
    hsuffix = ('.h', '.svg.h')['.svg' in suffix]
    context.update(
      classname=classname,
      guard='__%s__' % '_'.join(s.upper() for s in path + [classname]),
      header_file='/'.join(path + [classname + hsuffix]),
      namespace='\n'.join('namespace %s {' % p for p in path),
      namespace_end='\n'.join('}  // namespace %s' % p for p in reversed(path)),
      package='.'.join(path),
      )
    outSuffix, template = groups.getGroupTemplate(suffix)
    with open(name + outSuffix, 'w') as out:
      data = template.format(**context)
      out.write(data)
    print 'Written %s%s' % (name, outSuffix)


if __name__ == "__main__":
  new(*args.parseArgs())

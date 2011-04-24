#!/usr/local/bin/python

import glob
import os
import os.path
import re
import sys


def pathParts(s):
  parts = os.path.abspath(s).split('/src/rec/')[1:]
  if not parts:
    raise ValueError(s)
  parts = ['rec'] + parts[0].split('/')
  parts[-1] = parts[-1].split('.')[0]
  return parts


def run(cmd):
  # print '$', cmd
  os.system(cmd)


class Mover(object):
  NONE, START, BODY, END_NAME, END_GUARD, END = range(6)

  BLANK_PATTERN = '^\s+$'
  START_PATTERN = '^namespace \w+ {';
  END_PATTERN =  r'^}\s+// namespace \w+'
  GUARD_PATTERN =  r'^#endif\s+// __REC'

  FUNCTIONS = [(lambda path: '__' + '_'.join(p.upper() for p in path)),
               (lambda path: '#include "%s.h"' % '/'.join(path))]

  def __init__(self, fromFile, toFile):
    self.state = Mover.NONE
    self.fromFile, self.toFile = self.check(fromFile, toFile)

    fromPath = pathParts(self.fromFile)
    toPath = pathParts(self.toFile)
    self.replacements = [[f(fromPath), f(toPath)] for f in Mover.FUNCTIONS]

    names = toPath[:-1]
    def bed(names, begin, end='\n'):
      return begin + (end + begin).join(names) + end + '\n'

    self.namespaceStart = bed(names, 'namespace ', ' {\n')
    self.namespaceEnd =  bed(reversed(names), '}  // namespace ')

  def check(self, f, t):
    f, t = os.path.abspath(f), os.path.abspath(t)

    if not os.path.exists(f):
      raise ValueError(f + " doesn't exist!")

    if os.path.isdir(f):
      raise ValueError(f + ' is a directory!')

    if os.path.isdir(t):
      t += ('/' + os.path.basename(f))

    if os.path.exists(t):
      raise ValueError(t + ' already exists.')

    return f,t

  def move(self):
    tempFile = self.toFile + '.tmp'
    run('git mv %s %s' % (self.fromFile, self.toFile))
    if os.path.exists(self.fromFile):
      run('mv -f %s %s' % (self.fromFile, self.toFile))

    run('cp %s %s' % (self.toFile, tempFile))
    with open(tempFile, 'r') as input:
      with open(self.toFile, 'w') as output:
        self.out = output
        for line in input:
          self.transition(self.toState(line), line)
          self.process(line)
        self.transition(Mover.END, 'ENDENDEND')
    os.remove(tempFile)

  def toState(self, line):
    if re.match(Mover.BLANK_PATTERN, line):
      return self.state

    if self.state is Mover.NONE:
      return re.match(Mover.START_PATTERN, line) and Mover.START or Mover.NONE

    if self.state is Mover.START:
      return re.match(Mover.START_PATTERN, line) and Mover.START or Mover.BODY

    if re.match(Mover.END_PATTERN, line):
      return Mover.END_NAME

    if re.match(Mover.GUARD_PATTERN, line):
      return Mover.END_GUARD

    return Mover.BODY

  def transition(self, state, line):
    if self.state != state:
      if self.state is Mover.START:
        self.out.write(self.namespaceStart)

      if state is Mover.BODY:
        if self.state is Mover.END_GUARD:
          for x in self.endCache:
            self.out.write(x)
        self.endCache = []

      if state is Mover.END_GUARD:
        if self.state is Mover.END_GUARD:
          raise ValueError('Two end guards!')
        self.out.write(self.namespaceEnd)
        self.namespaceEnd = ''

      if state is Mover.END:
        self.out.write(self.namespaceEnd)
        self.namespaceEnd = ''

    self.state = state

  def process(self, line):
    if self.state in [Mover.NONE, Mover.BODY, Mover.END_GUARD]:
      for pat, repl in self.replacements:
        line = re.sub(pat, repl, line)
      self.out.write(line)

    elif self.state is Mover.END_NAME:
      self.endCache.append(line)


def move(args):
  to = args.pop()
  files = []
  for arg in args:
    results = glob.glob(arg)
    if results:
      files.extend(results)
    else:
      print arg, "didn't match any files."

  if not args:
    print ('Usage: mover.py fromFile toFileOrDirectory\n'
           '       mover.py from [...from] toDirectory')

  elif len(args) > 1 and not os.path.isdir(to):
     print 'Can only move multiple files to a directory:', to

  else:
    for a in args:
      Mover(a, to).move()

move(sys.argv[1:])

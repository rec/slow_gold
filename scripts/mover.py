#!/usr/local/bin/python

import glob
import os
import os.path
import re
import sys


class Mover(object):
  NONE = 0
  START = 1
  END = 2

  PATTERNS = {START: r'^namespace \w+ {',
              END: r'^}\s+// namespace \w+'}

  FUNCTIONS = [(lambda path: '__' + '_'.join(p.upper() for p in path)),
               (lambda path: '#include "%s.h"' % '/'.join(path)),
               (lambda path: path[-1])]

  def __init__(self, fromFile, toFile):
    def path(s):
      parts = os.path.abspath(s).split('/src/rec/')[1:]
      if not parts:
        raise ValueError(s)
      parts = ['rec'] + parts[0].split('/')
      parts[-1] = parts[-1].split('.')[0]
      return parts

    self.state = Mover.NONE
    fromFile = os.path.abspath(fromFile)
    toFile = os.path.abspath(toFile)

    if not os.path.exists(fromFile):
      raise ValueError(fromFile + " doesn't exist!")

    if os.path.isdir(fromFile):
      raise ValueError(fromFile + " is a directory!")

    self.fromFile = fromFile

    if os.path.isdir(toFile):
      toFile += ('/' + os.path.basename(fromFile))
    self.toFile = toFile

    fromPath = path(self.fromFile)
    toPath = path(self.toFile)

    func = Mover.FUNCTIONS
    self.replacements = [[f(fromPath), f(toPath)] for f in func]

    names = toPath[:-1]
    def bed(begin, end='\n'):
      return begin + (end + begin).join(names) + end

    self.namespace = [bed('namespace ', ' {\n'), bed('}  // namespace ')]

  def move(self):
    with open(self.fromFile, 'r') as input:
      with open(self.toFile, 'w') as output:
        self.out = output
        for line in input:
          self.transition(self.toState(line))
          self.process(line)

    os.remove(self.fromFile)

  def transition(self, state):
    if self.state != state and self.state:
      self.out.write(self.namespace[self.state - 1])
    self.state = state

  def toState(self, line):
    for state, pat in Mover.PATTERNS.iteritems():
      if re.match(pat, line):
        return state
    return Mover.NONE

  def process(self, line):
    if self.state == Mover.NONE:
      for pat, repl in self.replacements:
        line = re.sub(pat, repl, line)
      self.out.write(line)


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

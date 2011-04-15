#!/usr/local/bin/python

import os
import re
import sys

def getRoot():
  # TODO
  return '/Users/tom/Documents/development/rec/src/'

def embed(begin, items, end):
  return begin + (end + begin).join(items) + end

class Mover(object):
  NONE = 0
  START = 1
  END = 2

  PATTERNS = {START: r'^namespace \w+ {', END: r'^}\s+// namespace \w+'}
  FUNCTIONS = [(lambda path: '__' + '_'.join(p.upper() for p in path[:-1])),
               # (lambda path: '#include "%s/' % '/'.join(path[:-1])),
               (lambda path: path[-1]),
               ]


  def __init__(self, fr, to):
    def stripUp(s):
      prefix = '../'
      while s.startswith(prefix):
        s = s[len(prefix):]
      return ['rec'] + s.split('/')

    self.state = Mover.NONE
    self.fr = stripUp(fr)
    self.to = stripUp(to)
    if not self.to[-1]:
      self.to[-1] = self.fr[-1]

    self.replacements = [[f(self.fr), f(self.to)] for f in Mover.FUNCTIONS]
    self.namespace = [embed('namespace ', self.to[:-1], ' {\n'),
                      embed('}  // namespace ', self.to[:-1], '\n')]

  def move(self):
    r = getRoot()
    self.out = open(r + '/'.join(self.to), 'w')
    ifname = r + '/'.join(self.fr)
    infile = open(ifname, 'r')
    for line in infile:
      self.transition(self.toState(line))
      self.process(line)
    self.out.close()
    infile.close()
    os.remove(ifname)

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

#def move(fr, to):
#  Mover(fr, to).move()


def move(args):
  to = args.pop()
  if not args:
    print ('Usage: mover.py fromFile toFileOrDirectory\n'
           '       mover.py from [...from] toDirectory')

  elif len(args) > 1 and not to.endswith('/'):
    print 'Can only move multiple files to a directory'

  else:
    for a in args:
      Mover(a, to).move()

move(sys.argv[1:])

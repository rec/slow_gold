#!/usr/local/bin/python

import sys

STACK_DICT = {']': '[', ')': '(', '}': '{'}



def matchBrackets(f):
  stack = ''
  for number, line in enumerate(open(f)):
    for ch in line:
      if ch in '[({':
        stack += ch
      elif ch in '])}':
        if not stack:
          print '%s:%d found %s but stack was empty.' % (f, number, ch)
          return False
        elif stack[-1] is not STACK_DICT.get(ch, None):
          print '%s:%d found %s but stack had %s.' % (f, number, ch, stack[-1])
          return False
        stack = stack[:-1]

  if stack:
    print '%s:(end) stack had %s.' % (f, stack)

  return not stack

for f in sys.argv[1:]:
  matchBrackets(f)

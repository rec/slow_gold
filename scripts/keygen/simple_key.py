#!/usr/bin/python

import random
import sys

import badwords

VOWELS = 'aeiou'
CONSONANTS = 'bdfgklmnprstvz'
LETTERS = VOWELS, CONSONANTS
CAPITALIZE = True
BAD_INITIALS = ['l', 'i']

def isBad(key):
  return badwords.isBad(key) or (key[0] == BAD_INITIALS[CAPITALIZE])

def firstIndex():
  return random.randrange(len(VOWELS) + len(CONSONANTS)) >= len(VOWELS)

def randomKey(length):
  s = ''
  index = firstIndex()
  for i in range(length):
    s += random.choice(LETTERS[index])
    index = not index
  return s

def goodRandomKey(length):
  while True:
    key = randomKey(length)
    if not isBad(key):
      return CAPITALIZE and key.capitalize() or key

def makeKey(first, second):
  if second:
    return '%s %s' % (goodRandomKey(first), goodRandomKey(second))
  else:
    return goodRandomKey(first)

def parseArgs(first = 12, second = 0, count = 1):
  return int(first), int(second), int(count)

if __name__ == '__main__':
  first, second, count = parseArgs(*sys.argv[1:])
  for i in xrange(count):
    if second:
      print '%s %s' % (goodRandomKey(first), goodRandomKey(second))
    else:
      print randomKey(first)

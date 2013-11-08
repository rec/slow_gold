#!/usr/bin/python

import random
import sys

import badwords

VOWELS = 'aeiou'
CONSONANTS = 'bdfgklmnprstvz'
LETTERS = VOWELS, CONSONANTS
CAPITALIZE = True
BAD_INITIALS = ['l', 'i']
TERMINAL_PUNCTUATION = ['.', '...', '!', '?', '!!', '!?', '?!', '??']

def is_bad(key):
  return badwords.is_bad(key) or (key[0] == BAD_INITIALS[CAPITALIZE])

def first_index():
  return random.randrange(len(VOWELS) + len(CONSONANTS)) >= len(VOWELS)

def random_key(length):
  s = ''
  index = first_index()
  for i in range(length):
    s += random.choice(LETTERS[index])
    index = not index
  return s

def good_random_key(length):
  while True:
    key = random_key(length)
    if not is_bad(key):
      return CAPITALIZE and key.capitalize() or key

def make_key(first, second=0):
  if second:
    return '%s %s' % (good_random_key(first), good_random_key(second))
  else:
    return good_random_key(first)

def parse_args(first = 12, second = 0, count = 1):
  return int(first), int(second), int(count)

if __name__ == '__main__':
  first, second, count = parse_args(*sys.argv[1:])
  for i in xrange(count):
    if second:
      print '%s.%s' % (good_random_key(first), good_random_key(second))
    else:
      print random_key(first)

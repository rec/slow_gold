#!/usr/bin/python

import random
import sys

VOWELS = 'aeiou'
CONSONANTS = 'bdfglmnprsvwz'
LETTERS = VOWELS, CONSONANTS

def randomKey(length):
  s = ''
  index = random.randrange(2)
  for i in range(length):
    s += random.choice(LETTERS[index])
    index = 1 - index
  return s


if __name__ == '__main__':
  first = 10
  second = 0
  count = 1
  if len(sys.argv) > 1:
    first = int(sys.argv[1])
    if len(sys.argv) > 2:
      second = int(sys.argv[2])
      if len(sys.argv) > 3:
        count = int(sys.argv[3])

  for i in xrange(count):
    if second:
      print randomKey(first) + '-' + randomKey(second)
    else:
      print randomKey(first)

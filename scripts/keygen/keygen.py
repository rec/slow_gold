#!/usr/bin/python

import random
import re
import sys

VOWELS = re.compile('([aeiou]+)')
WORD = re.compile('[^a-zA-Z]')

class Accum(object):
  def __init__(self):
    self.total = 0
    self._accum = {}

  def accum(self, x):
    self.total += 1
    self._accum[x] = self._accum.get(x, 0) + 1

  def random(self):
    r = random.randrange(self.total)
    for k, v in self._accum.iteritems():
      r -= v
      if r < 0:
        return k

  def __str__(self):
    return 'Accum(%d, %s)' % (self.total, str(self._accum))


class PartAccum(object):
  def __init__(self):
    self.vowels = Accum()
    self.consonants = Accum()

  def getPart(self, isVowel):
    return self.vowels if isVowel else self.consonants

  def accum(self, x):
    self.getPart(VOWELS.match(x)).accum(x)

  def randomIsVowel(self):
    total = self.vowels.total + self.consonants.total
    return (random.randrange(total) < self.vowels.total)

  def random(self, isVowel):
    return self.getPart(isVowel).random()

  def __str__(self):
    return 'PartAccum(%s, %s)' % (str(self.vowels), str(self.consonants))


class Distribution(object):
  def __init__(self):
    self.total = 0
    self.lengths = Accum()
    self.first = PartAccum()
    self.last = PartAccum()
    self.singleton = PartAccum()
    self.middle = PartAccum()

  def addWordParts(self, parts):
    self.total += 1
    self.lengths.accum(len(parts))
    self.first.accum(parts[0])
    self.last.accum(parts[-1])
    if len(parts) is 1:
      self.singleton.accum(parts[0])
    else:
      for p in parts[1:-1]:
        self.middle.accum(p)

  def addSentences(self, sentences):
    for s in sentences:
      for word in WORD.split(s):
        parts = filter(None, VOWELS.split(word.lower()))
        if parts:
          self.addWordParts(parts)

  def random(self):
    def rand():
      length = self.lengths.random()
      if length is 1:
        yield self.singleton.random()

      isVowel = self.first.randomIsVowel()
      yield self.first.random(isVowel)
      for i in xrange(1, length - 1):
        isVowel = not isVowel
        yield self.middle.random(isVowel)

      isVowel = not isVowel
      yield self.last.random(isVowel)
    return ''.join(rand())

  def __str__(self):
    return (str(self.first) + '\n' +
            str(self.last) + '\n' +
            str(self.singleton) + '\n' +
            str(self.middle) + '\n' +
            str(self.lengths))


if __name__ == '__main__':
  d = Distribution()
  f = sys.argv[1]
  print f
  d.addSentences(open(f, 'r'))
  print d

  for i in xrange(20):
    print d.random()

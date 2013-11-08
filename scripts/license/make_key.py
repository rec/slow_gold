from __future__ import absolute_import, division, print_function, unicode_literals

from passay import passay

VOWELS = 'aeiou'
CONSONANTS = 'bdfgklmnprstvz'

GENERATOR = passay.PasswordGenerator(
  words=[6, 9],
  vowels=VOWELS,
  consonants=CONSONANTS,
  punctuation=[],
  pairs=None,
  numbers=0,
  word_start=passay.LetterType.BOTH,
  separator=' ',
  capitalize=passay.Capitalize.FIRST,
  bad=None)

def make_key():
  return passay.make_password(GENERATOR)

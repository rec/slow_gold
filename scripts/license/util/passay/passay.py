from collections import namedtuple

import random

from util.passay import badwords
from util import Enum

PasswordGenerator = namedtuple(
  'PasswordGenerator',
  ['words', 'vowels', 'consonants', 'pairs', 'punctuation', 'numbers',
   'word_start', 'separator', 'capitalize', 'bad'])

Capitalize = Enum('NONE', 'FIRST', 'WORDS')
LetterType = Enum('CONSONANT', 'VOWEL', 'BOTH')

Pairs = namedtuple('Pairs', ['initial', 'middle', 'terminal'])
Bad = namedtuple('Bad', ['initial', 'terminal'])

NUMBERS = '0123456789'

def make_letter(generator, letter_type, is_initial, is_terminal,
                choice=random.choice):
  if letter_type is LetterType.CONSONANT:
    letters = generator.consonants
    if generator.pairs:
      if is_initial:
        letters += generator.pairs.initial
      elif is_terminal:
        letters += generator.pairs.terminal
      else:
        letters += generator.pairs.middle
    letter_type = LetterType.VOWEL
  else:
    letters = generator.vowels
    letter_type = LetterType.CONSONANT

  if generator.bad:
    if is_initial:
      letters = set(letters) - set(generator.bad.initial)
    elif is_terminal:
      letters = set(letters) - set(generator.bad.terminal)

  return choice(letters), letter_type

def make_word(generator, length, choice=random.choice):
  while True:
    parts = []
    letter_type = generator.word_start
    if letter_type is LetterType.BOTH:
      letter_type = choice([LetterType.CONSONANT, LetterType.VOWEL])

    for i in xrange(length):
      letter, letter_type = make_letter(generator, letter_type,
                                        not i, i == (length - 1), choice=choice)
      parts.append(letter)

    word = ''.join(parts)
    if not badwords.is_bad(word):
      return word

def make_password(generator, choice=random.choice):
  words = [make_word(generator, w, choice) for w in generator.words]
  if generator.capitalize is Capitalize.FIRST:
    if words:
      words[0] = words[0].capitalize()
  elif generator.capitalize is Capitalize.WORDS:
    words = [w.capitalize() for w in words]
  if generator.numbers:
    word = ''.join(choice(NUMBERS) for i in xrange(generator.numbers))
    words.append(word)
  result = generator.separator.join(words)
  return result + choice(generator.punctuation)



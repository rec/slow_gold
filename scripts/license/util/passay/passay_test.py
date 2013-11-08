"""

>>> passay.make_letter(generator, passay.LetterType.VOWEL, False, False, choose_first)[0]
'a'

>>> passay.make_letter(generator, passay.LetterType.CONSONANT, False, False, choose_first)[0]
'b'

>>> passay.make_letter(generator, passay.LetterType.VOWEL, False, False, new_random())[0]
'a'

>>> passay.make_letter(generator, passay.LetterType.CONSONANT, False, False, new_random())[0]
'f'

>>> passay.make_word(generator, 5, choose_first)
'babab'

>>> passay.make_word(generator, 5, new_random())
'morom'

>>> passay.make_password(generator, choose_first)
'Babab babababa 000.'

>>> passay.make_password(generator, new_random())
'Morom idibuzek 721...'

"""

import passay
import random

VOWELS = 'aeiou'
CONSONANTS = 'bdfgklmnprstvz'
TERMINAL_PUNCTUATION = ['.', '...', '!', '?', '!!', '!?', '?!', '??']

generator = passay.PasswordGenerator(
  words=[5, 8],
  vowels=VOWELS,
  consonants=CONSONANTS,
  punctuation=TERMINAL_PUNCTUATION,
  pairs=None,
  numbers=3,
  word_start=passay.LetterType.BOTH,
  separator=' ',
  capitalize=passay.Capitalize.FIRST,
  bad=None)

def choose_first(x):
  for i in x:
    return i

CHOICES = []

def new_random():
  random.seed(100)

  def choice(x):
    CHOICES.append(x)
    return random.choice(x)

  return choice

#!/usr/bin/python

BADWORDS = (
  'dago',
  'fag',
  'gag',
  'gip',
  'kok',
  'kul',
  'kun',
  'nig',
  'pak',
  'pus',
  'tit',
  'wop',
  )

def isBad(word):
  for w in BADWORDS:
    if w in word:
      return True

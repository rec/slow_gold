#!/usr/bin/python

BADWORDS = (
  'dago',
  'fag',
  'fok',
  'fuk',
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

def is_bad(word):
  for w in BADWORDS:
    if w in word:
      return True

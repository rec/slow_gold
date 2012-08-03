#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: mergeTranslations [rootfile]"""

FIXES = (
  ('"% s"', '"%s"'),
  ('(% s)', '(%s)'),
  ('% S', '%s'),
  ('% s', ' %s'),
  ('% d', ' %d'),
  )

def fixStrings(s):
  for f in FIXES:
    s = s.replace(*f);
  return s

def mergeRemoved(english, translated, newTranslation):
  result = translate.TranslatedStrings()
  result.max_index = english.max_index

  for k, v in translated.dict.iteritems():
    if k not in english.dict:
      result.strings.add()->CopyFrom(value)
  return result

def mergeOriginal(english, translated, newTranslation):
  result = translate.TranslatedStrings()
  result.max_index = english.max_index

  for k, v in english.dict.iteritems():
    resultString = result.strings.add()
    new = newTranslation.dict.get(v.index, None)
    resultString.CopyFrom(v)
    if new:
      resultString.translation = proto.encode(new)
    else:
      old = translated.dict.get(k, None)
      if old:
        resultString.CopyFrom(old)
      else:
        print "oops!", k

  return result

def mergeOne(root, lang):
  english = translate.ProtoFile(root=root)
  english.read()

  translated = translate.ProtoFile(root=root, lang=lang)
  translated.read()

  newTranslationLines = translate.TextFile(root=root, lang=lang, prefix='un')
  newTranslationLines.read()

  newTranslated = mergeOriginal(english, translated, newTranslationLines)
  english.write(newTranslated)

  newRemoved = mergeRemoved(english, translated, newTranslation)
  removed = translate.ProtoFile(root=root, lang=lang, prefix='removed-')
  removed.write(newRemoved)

def mergeTranslations(root):
  for lang in translate.LANGUAGES:
    if lang != 'en':
      mergeOne(root, lang):

if __name__ == '__main__':
  if len(sys.argv) is 3:
    mt = mergeTranslations(sys.argv[1:])

  else:
    print USAGE

#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: extractUntranslated.py [rootfile]"""
PRINT_LINE_NUMBERS = False
PRINT_TRANSLATION = False

def extractOne(lang, root):
  original = translate.ProtoFile(root=root)
  original.read()

  translated = translate.ProtoFile(root=root, lang=lang)
  translated.read()

  lines = []

  for k, v in original.dict.iteritems():
    if k not in translated.dict:
      lines.append('%d. %s' % (v.index, proto.encode(v.original)))

  translate.TextFile(root=root, lang=lang, prefix='un').write(lines)

def extractUntranslated(root):
  for lang in translate.LANGUAGES:
    if lang != 'en':
      extractOne(lang, root)

if __name__ == '__main__':
  if len(sys.argv) < 3:
    extractUntranslated(sys.argv[1:])
  else:
    print USAGE


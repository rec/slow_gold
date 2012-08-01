#!/usr/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')
sys.path.append('/development/rec/scripts/jucer')

from google.protobuf import text_format
from Trans_pb2 import TranslatedStrings, TranslationUpdate
from odict import OrderedDict

USAGE = """Usage: translate oldfile newfile"""

def utf8(x):
  return unicode(x, 'utf-8');

def readProto(proto, file):
  t = proto()
  text_format.Merge(utf8(open(file, 'r').read()), t)
  return t

def readStringDictionary(file):
  t = readProto(TranslatedStrings, file)
  return OrderedDict(((s.original, s.hint), s) for s in t.str)

def mergeTranslation(oldfile, newfile):
  old = readStringDictionary(oldfile)
  new = readStringDictionary(newfile)
  update = TranslationUpdate()

  for key, value in old.iteritems():
    bucket = update.unchanged if key in new else update.leaving
    bucket.str.add().CopyFrom(value)

  for key, value in new.iteritems():
    if key not in old:
      update.entering.str.add().CopyFrom(value)

  return update

def readNewTranslations(oldfile, newfile):
  update = mergeTranslation(oldfile, newfile)
  print '*** LEAVING ***'
  text_format.PrintMessage(update.leaving, sys.stdout)

  result = TranslatedStrings()
  result.str.MergeFrom(update.unchanged.str)

  for s in update.entering.str:
    msg = '%s: ' % s.original
    if s.hint:
      msg = '%s [%s]' % (msg, s.hint)
    print msg,
    tr = utf8(raw_input()).strip()
    if tr:
      t = result.str.add()
      t.CopyFrom(s)
      t.translation = tr
  return result

PRINT_LINE_NUMBERS = False

def printCurrentTranslation(oldfile):
  old = readProto(TranslatedStrings, oldfile)
  for i, x in enumerate(old.str):
    s = x.original.encode('utf-8')
    if PRINT_LINE_NUMBERS:
      print '%d: %s' % (i, s)
    else:
      print s

if __name__ == '__main__':
  if len(sys.argv) is 2:
    printCurrentTranslation(sys.argv[1])

  elif len(sys.argv) is 3:
    t = readNewTranslations(*sys.argv[1:])
    text_format.PrintMessage(t, sys.stdout)

  else:
    print USAGE


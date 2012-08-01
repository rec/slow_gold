#!/usr/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')
sys.path.append('/development/rec/scripts/jucer')

import proto

from google.protobuf import text_format
from Trans_pb2 import TranslatedStrings, TranslationUpdate
from odict import OrderedDict

def readStringDictionary(file):
  t = proto.read(TranslatedStrings, file)
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
  proto.write(update.leaving)

  result = TranslatedStrings()
  result.str.MergeFrom(update.unchanged.str)

  for s in update.entering.str:
    msg = '%s: ' % s.original
    if s.hint:
      msg = '%s [%s]' % (msg, s.hint)
    print msg,
    tr = proto.decode(raw_input()).strip()
    if tr:
      t = result.str.add()
      t.CopyFrom(s)
      t.translation = tr
  return result

PRINT_LINE_NUMBERS = False

def printCurrentTranslation(oldfile):
  old = proto.read(TranslatedStrings, oldfile)
  for i, x in enumerate(old.str):
    s = proto.encode(x.original)
    if PRINT_LINE_NUMBERS:
      print '%d: %s' % (i, s)
    else:
      print s


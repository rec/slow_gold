#!/usr/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')
sys.path.append('/development/rec/scripts/jucer')

import proto

from google.protobuf import text_format
from Trans_pb2 import TranslatedStrings, TranslationUpdate
from odict import OrderedDict


def readStrings(file):
  return proto.read(TranslatedStrings, file)

def readStringDictionary(file):
  t = readStrings(file)
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

def stringName(s):
  msg = '%s: ' % s.original
  if s.hint:
    msg = '%s [%s]' % (msg, s.hint)
  return proto.encode(msg)

def readNewTranslations(oldfile, newfile):
  update = mergeTranslation(oldfile, newfile)
  print '*** LEAVING ***'
  proto.write(update.leaving)

  result = TranslatedStrings()
  result.str.MergeFrom(update.unchanged.str)

  for s in update.entering.str:
    print stringName(s),
    tr = proto.input()
    if tr:
      t = result.str.add()
      t.CopyFrom(s)
      t.translation = tr
  return result

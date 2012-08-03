#!/usr/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')
sys.path.append('/development/rec/scripts/jucer')

import proto

from google.protobuf import text_format
from Trans_pb2 import TranslatedString, TranslatedStrings, TranslationUpdate
from odict import OrderedDict

DEFAULT_ROOT_DIRECTORY = '/development/rec/text'
LANGUAGES = 'de', 'en', 'es', 'fr', 'id'
PROTO_FILE = 'rec.TranslatedStrings'
TEXT_FILE = 'translated.txt'

class File(object):
  def __init__(self, baseFile, lang='en', root=[]):
    path = root[0] if root else DEFAULT_ROOT_DIRECTORY
    self.file = '/'.join([path, lang, baseFile])
    self.strings = None

class ProtoFile(File):
  def __init__(self, prefix='', **kwds):
    File.__init__(self, prefix + PROTO_FILE, **kwds)
    self.dict = None

  def read(self):
    self.strings = proto.read(TranslatedStrings, self.file)
    self.dict = toStringDictionary(self.strings)

  def write(self, value):
    proto.write(value, open(self.file, 'w'))


class TextFile(File):
  def __init__(self, prefix='', **kwds):
    File.__init__(self, prefix + TEXT_FILE, **kwds)

  def read(self):
    self.strings = open(self.file, 'r').readLines()

  def write(self, value):
    raise Exception('Can only write protos')


def readStrings(file):
  return proto.read(TranslatedStrings, file)

def toStringDictionary(t):
  return OrderedDict(((s.original, s.hint), s) for s in t.str)

def readStringDictionary(file):
  return toStringDictionary(readStrings(file))

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
  msg = s.original
  if s.index:
    msg = '%d. %s' % msg
  if s.hint:
    msg = '%s [%s]' % (msg, s.hint)
  return proto.encode(msg)

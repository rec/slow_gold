#!/usr/local/bin/python

import sys

sys.path.append('/development/rec/genfiles/proto/rec/base')
sys.path.append('/development/rec/scripts/jucer')

import proto

from google.protobuf import text_format
from Trans_pb2 import TranslatedString, TranslatedStrings
from odict import OrderedDict

DEFAULT_ROOT_DIRECTORY = '/development/rec/text'
LANGUAGES = 'de', 'en', 'es', 'fr', 'id'
PROTO_FILE = 'TranslatedStrings.def'
TEXT_FILE = 'translated.txt'

def splitLine(s):
  pos = s.find(' ')
  line = s[pos + 1:]
  if pos < 1:
    print '!!!', s
  if s[pos - 1] is '.':
    pos -= 1
  return int(s[0:pos]), line

def toStringDictionary(t):
  return OrderedDict(((s.original, s.hint), s) for s in t.str)


class File(object):
  def __init__(self, baseFile, lang='en', root=[]):
    path = root[0] if root else DEFAULT_ROOT_DIRECTORY
    self.filename = '-'.join(['/'.join([path, lang]), baseFile])
    self.strings = None
    self.dict = None

class ProtoFile(File):
  def __init__(self, prefix='', **kwds):
    File.__init__(self, prefix + PROTO_FILE, **kwds)

  def read(self):
    self.strings = proto.read(TranslatedStrings, self.filename)
    self.dict = toStringDictionary(self.strings)

  def write(self, value):
    proto.write(value, open(self.filename, 'w'))


class TextFile(File):
  def __init__(self, prefix='', **kwds):
    File.__init__(self, prefix + TEXT_FILE, **kwds)

  def read(self):
    lines = open(self.filename, 'r').readlines()
    self.strings = [s.strip() for s in lines if s]
    self.dict = dict(splitLine(s.strip()) for s in self.strings)

  def write(self, lines):
    f = open(self.filename, 'w').writelines('%s\n' % i for i in lines)

def stringName(s):
  msg = s.original
  if s.index:
    msg = '%d. %s' % msg
  if s.hint:
    msg = '%s [%s]' % (msg, s.hint)
  return proto.encode(msg)

#!/usr/bin/python

import sys

from google.protobuf import text_format

def decode(x):
  return unicode(x, 'utf-8')

def encode(x):
  return x.encode('utf-8');

def read(proto, file):
  t = proto()
  f = ''
  try:
    f = open(file, 'r').read()
  except:
    print "Couldn't read file", file
    pass

  text_format.Merge(decode(f), t)
  return t

def write(p, out=sys.stdout):
  text_format.PrintMessage(p, out);

def toString(p):
  return text_format.MessageToString(p)

def input(*args):
  return decode(raw_input(*args)).strip()

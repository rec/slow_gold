#!/usr/bin/python

import sys

import proto
import translate

USAGE = """Usage: mergeIncoming [rootDirectory]"""

PRINT_DIAGNOSTICS = False

def writeRemoved(old, new):
  removed = translate.TranslatedStrings()
  removed.max_index = old.strings.max_index

  for key, value in old.dict.iteritems():
    if key not in new.dict:
      removed.str.add.CopyFrom(value)

  translate.ProtoFile(prefix='removed-').write(removed)

def writeNew(old, new):
  result = translate.TranslatedStrings()
  result.max_index = old.strings.max_index

  for key, value in new.dict.iteritems():
    newValue = old.dict.get(key, None)
    if not newValue:
      newValue = value
      result.max_index += 1
      newValue.index = result.max_index
      newValue.ClearField('translation')

    result.str.add().CopyFrom(newValue)

  old.write(result)

def mergeIncoming(*root):
  old = translate.ProtoFile(root=root)
  new = translate.ProtoFile(prefix='incoming-', root=root)
  old.read()
  new.read()

  writeRemoved(old, new)
  writeNew(old, new)


if __name__ == '__main__':
  if len(sys.argv) <= 2:
    mergeIncoming(*sys.argv[1:])
  else:
    print USAGE


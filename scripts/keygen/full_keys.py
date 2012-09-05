#!/usr/bin/python

import random
import subprocess
import sys

import simple_key

IS_MAC = True

KEYS = ('AzmiwE.o8kcljaggx32nT3k8e2k7AwwytE1693b8v4tfb9b7Egrj.eEcB2mrgtsq',
        'iJEyX3XV6fuqMoEDMwuU5W0PuV2gNlZDHBVK0w4B7dxNrrGpvugOZdJjrPVm7Xkn')

BINARY = '/development/rec/projects/keymaker/build/Debug/keymaker'

NAME_RANGE = (6, 9)


def makeKey(name):
  popen = subprocess.Popen((BINARY, '-30', name, KEYS[IS_MAC]),
                           stdout=subprocess.PIPE)
  popen.wait()
  return popen.stdout.read().strip()

def makeName():
  first = random.randrange(*NAME_RANGE)
  second = random.randrange(*NAME_RANGE)
  return simple_key.makeKey(first, second)

def printNameKey(name, key):
  print '"%s", "%s"' % (name, key)


if __name__ == '__main__':
  first, second, count = simple_key.parseArgs(*sys.argv[1:])
  printNameKey('Name', 'Key')
  for i in xrange(count):
    name = makeName()
    printNameKey(name, makeKey(name))

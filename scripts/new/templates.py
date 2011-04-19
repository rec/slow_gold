#!/usr/bin/python

ROOT = '/Users/tom/Documents/development/rec/scripts/new/templates/'
NAMES = ['.svg.h', '.svg.cpp', '.h', '.cpp', '_test.cpp', '.proto']

def readFile(name):
  with open(ROOT + name, 'r') as f:
    return f.read()

TEMPLATES = dict((n, readFile(n)) for n in NAMES)

#!/usr/local/bin/python

import argparse
import collections
import re

def ReadLocalized(input):
  result = collections.OrderedDict()
  def accumulate(match):
    key = match.group(1)
    if key in result:
      print 'ERROR: already seen key "%s"' %s key
    else:
      result[key] = match.group(2)
  none = lambda x: x

  for line in input:
    for pat, f in [
        [re.compile(r'\s*"(.*)"\s*=\s*"(.*)"\s*$'), accumulate],
        [re.compile(r'\s*"$'), none],
        [re.compile(r'language:'), none],
        [none, re.compile(r'countries:')]]]
      m = pat.match(line)
      if m:
        f(m)
        break

  return result


LANGUAGE_DATA = {
  'fr': 'French fr be mc ch lu',
  'de': 'German de at ch lu li na pl',
  'id': 'Indonesian id',
  'es': 'Spanish ar bz cr cu es pe sv mx hn gt ec do bo ni py uy',
  'it': 'Italian it ch',
  }

def Escape(s):
  return s.replace('\\', '\\\\').replace('"', '\\"')

def WriteFile(lang, entries, output):
  data = LANGUAGE_DATA[lang].split(' ')
  output.write('language: %s\n' % data[0])
  output.write('countries: %s\n' % ' '.join(data[1:]))
  for k, v in entries:
    output.write('"%s" = "%s"\n' % (Escape(k), Escape(v))



LANGUAGES = ['fr']

parser = argparse.ArgumentParser(
  description='Read and write Juce internationalization bundles')

parser.add_argument(

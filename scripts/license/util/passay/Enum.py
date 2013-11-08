from __future__ import absolute_import, division, print_function, unicode_literals

import copy

class Enum(object):
  def __init__(self, *sequential, **named):
    self._sequential = sequential
    self._named = named
    self._values = range(len(sequential))
    self._values.extend(named)

    self._keys = list(sequential)
    self._keys.extend(named.keys())

    self._reverse = {}
    for i, s in enumerate(sequential):
      setattr(self, s, i)
      self._reverse[i] = s
    for k, v in named.iteritems():
      setattr(self, k, v)
      self._reverse[v] = k

  def reverse(self, key):
    return self._reverse[key]

  def __iter__(self):
    return iter(self._keys)

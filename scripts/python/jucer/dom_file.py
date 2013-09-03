#!/usr/local/bin/python
#
# Create elements for Jucer-style DOM trees.
#
# Copyright (c) 2010 Tom Swirly
# This software is licensed under the terms of the artistic license,
# http://www.opensource.org/licenses/artistic-license-2.0.php
# Essentially, you can do as you please with it.  Have fun!

import os.path
import random
import xml.dom.minidom

RANDOMIZE_IDS = not True

def randomId():
  return ''.join(random.choice(DomFile.CHARS) for i in xrange(DomFile.ID_SIZE))

class DomFile:
  """Creates XML DOM elements that have Jucer-style 9-character random IDs."""

  CHARS = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
  """Legal characters for Jucer ID."""

  ID_SIZE = 9
  """Length of Jucer ID."""

  def __init__(self, filename):
    self.dom = xml.dom.minidom.parse(open(filename))
    self.documentElement = self.dom.documentElement

  def compute_dict(self, node):
    self.file_id_dict = get_file_id_dict(node)

  def create(self, xml_name, path, **attributes):
    id = None
    if not RANDOMIZE_IDS:
      id = self.file_id_dict.get(os.path.join(path, attributes['name']))
    attributes['id'] = id or randomId()
    element = self.dom.createElement(xml_name)
    element.setAttribute('id', randomId())
    for k, v in attributes.iteritems():
      element.setAttribute(k, v)
    return element

  def element(self, *tag_names):
    """Get an element in the DOM tree by a sequence of tag_names.  If there are
       multiple tag names with the same tag, selects the first at each stage."""
    node = self.documentElement
    for n in tag_names:
      node = node.getElementsByTagName(n)[0]

    return node


def get_file_id_dict(node, path='', depth=0, result=None):
  result = result or {}
  if path:
    path += '/'
  path += node.getAttribute('name')

  result[path] = node.getAttribute('id')
  for c in node.childNodes:
    if (hasattr(c, 'tagName') and c.tagName in ['GROUP', 'FILE']):
      get_file_id_dict(c, path, depth + 1, result)
  return result



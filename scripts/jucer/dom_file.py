#!/usr/local/bin/python

import random
import xml.dom.minidom


class DomFile:
  CHARS = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
  ID_SIZE = 9

  def __init__(self, filename):
    self.dom = xml.dom.minidom.parse(open(filename))
    self.documentElement = self.dom.documentElement


  def create(self, xml_name, **attributes):
    element = self.dom.createElement(xml_name)

    id = ''.join(random.choice(DomFile.CHARS) for i in xrange(DomFile.ID_SIZE))
    element.setAttribute('id', id)

    for k, v in attributes.iteritems():
      element.setAttribute(k, v)
    return element


  def element(self, *names):
    node = self.documentElement
    for n in names:
      node = node.getElementsByTagName(n)[0]
    return node

#!/usr/local/bin/python

import sys
import xml.dom.minidom

print xml.dom.minidom.parse(open(sys.argv[1])).toprettyxml()

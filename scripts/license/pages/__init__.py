from __future__ import absolute_import, division, print_function, unicode_literals

import jinja2
import os.path

_HTML = os.path.join(os.path.dirname(os.path.dirname(__file__), 'html'))

JINJA_ENVIRONMENT = jinja2.Environment(
  loader=jinja2.FileSystemLoader(_HTML),
  extensions=['jinja2.ext.autoescape'],
  autoescape=True)

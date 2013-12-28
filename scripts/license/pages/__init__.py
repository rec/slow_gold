from __future__ import absolute_import, division, print_function, unicode_literals

import jinja2
import os.path
import webapp2

_HTML = os.path.join(os.path.dirname(os.path.dirname(__file__), 'html'))

JINJA_ENVIRONMENT = jinja2.Environment(
  loader=jinja2.FileSystemLoader(_HTML),
  extensions=['jinja2.ext.autoescape'],
  autoescape=True)

class RequestHandler(webapp2.RequestHandler):
  def write_template(self, template, values=None, **kwds):
    if values:
      if kwds:
        kwds.update(values)
        values = kwds
    else:
      values = kwds
    self.response.write(JINJA_ENVIRONMENT.get_template(template).render(values))


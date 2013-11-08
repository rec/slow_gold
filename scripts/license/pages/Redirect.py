from __future__ import absolute_import, division, print_function, unicode_literals

import webapp2

class Redirect(webapp2.RequestHandler):
  def get(self):
    self.redirect('http://slowgold.com', permanent=True)

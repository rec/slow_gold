from __future__ import absolute_import, division, print_function, unicode_literals

from pages import RequestHandler

class Redirect(RequestHandler):
  def get(self):
    self.redirect('http://slowgold.com', permanent=True)

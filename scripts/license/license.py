import cgi
import os
import urllib

from google.appengine.api import users
from google.appengine.ext import ndb

import jinja2
import webapp2

JINJA_ENVIRONMENT = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(__file__)),
    extensions=['jinja2.ext.autoescape'],
    autoescape=True)


class License(ndb.Model):
  author = ndb.UserProperty()
  key = ndb.StringProperty()
  user_name = ndb.StringProperty()
  expiration = ndb.DateTimeProperty()

  mac_address = ndb.StringProperty(repeated=True)
  registration = ndb.StringProperty(repeated=True)


class Redirect(webapp2.RequestHandler):
    def get(self):
      self.redirect('http://slowgold.com')

application = webapp2.WSGIApplication([
    ('/', Redirect),
    # ('/register', Register),
    # ('/admin', Admin),
    # ('/add_keys', AddKeys),
    # ('/view', View),
], debug=True)


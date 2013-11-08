import cgi
import datetime
import jinja2
import os.path
import urllib
import webapp2
import yaml

from google.appengine.api import users
from google.appengine.ext import ndb

import license

HTML_FILES = os.path.join(os.path.dirname(__file__))

JINJA_ENVIRONMENT = jinja2.Environment(
  loader=jinja2.FileSystemLoader(HTML_FILES),
  extensions=['jinja2.ext.autoescape'],
  autoescape=True)


class Redirect(webapp2.RequestHandler):
  def get(self):
    self.redirect('http://slowgold.com', permanent=True)


class Register(webapp2.RequestHandler):
  def get(self):
    try:
      license = self._get_license()
      result = {'expiration': license.expiration}

    except Exception as e:
      result = {'error': str(e)}

    self.response.write(yaml.safe_dump(result))

  def _get_license(self);
    hardware_key = self.request.get('hardware_key', '')
    license_key = self.request.get('license_key', '')
    product = self.request.get('product', '')
    machine_info = self.request.get('machine_info', '')

    if license_key:
      user_name = self.request.get('user_name', '')
      return license.claim(
        hardware_key, license_key, machine_info, product, user_name)
    else:
      return license.trial(hardware_key, machine_info, product)


class Admin(webapp2.RequestHandler):
  def get(self):
    pass

class AddKeys(webapp2.RequestHandler):
  def get(self):
    pass


application = webapp2.WSGIApplication([
    ('/', Redirect),
    ('/register', Register),
    # ('/admin', Admin),
    ('/add_keys', AddKeys),
    # ('/view', View),
], debug=True)

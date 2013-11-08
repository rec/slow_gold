from __future__ import absolute_import, division, print_function, unicode_literals

import webapp2

from pages import AddKeys, Admin, Redirect, Register

application = webapp2.WSGIApplication([
    ('/admin', Admin),
    ('/add_keys', AddKeys),
    ('/', Redirect),
    ('/register', Register),
], debug=True)

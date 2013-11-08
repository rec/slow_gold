from importlib import import_module
import webapp2

from pages.Register import Register

_PAGES = 'Add', 'Admin', 'Create', 'Find', 'Register'

_PARTS = [('/' + p, getattr(import_module(p), p)) for p in _PAGES]
_PARTS.append(('/', Register.Register))
application = webapp2.WSGIApplication(_PARTS, debug=True)


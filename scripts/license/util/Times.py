from __future__ import absolute_import, division, print_function, unicode_literals

import datetime

DEFAULT_EXPIRATION_DAYS = 15
EXPIRATIONS = {'slowgold': 15}

now = datetime.datetime.utcnow

def expiration(product):
  days = EXPIRATIONS.get(product, DEFAULT_EXPIRATION_DAYS)
  return now() + datetime.timedelta(days=days)


from __future__ import absolute_import, division, print_function, unicode_literals

import datetime

DEFAULT_EXPIRATION = datetime.timedelta(days=15)

now = datetime.datetime.utcnow

EXPIRATIONS = {}

def expiration(product):
  return now() + EXPIRATIONS.get(PRODUCT, DEFAULT_EXPIRATION)


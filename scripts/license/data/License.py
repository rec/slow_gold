import logging

from google.appengine.api import users
from google.appengine.ext import ndb

from util import MakeKey
from util import Times

class License(ndb.Model):
  claims = ndb.StructuredProperty(repeated=True)
  created_by = ndb.UserProperty()
  creation_time = ndb.DateTimeProperty(auto_now_add=True)
  distributed = ndb.BooleanProperty()
  distributed_by = ndb.UserProperty()
  distribution_time = ndb.DateTimeProperty()
  expiration = ndb.DateTimeProperty()
  license_key = ndb.StringProperty()
  product = ndb.StringProperty()

  def test(self, condition, msg, *args):
    if not condition:
      raise Exception(msg % (('license key ' + self.license_key),) + args)

  def distribute(self, license_key):
    self.test(license.distributed, 'Tried to distribute %s twice')
    self.distributed = True
    self.distribution_time = Times.now()
    self.distributed_by = users.get_current_user()
    self.put()

  def make_claim(self, claim, product):
    self.test(self.product == product,
              'Wrong product for %s: expected %s, got %s' %
              product, self.product)

    if not self.distributed:
      logging.warning('Claimed undistributed license key %s', self.license_key)

    if any(c.hardware_key == claim.hardware_key for c in self.claims):
      logging.warning('Second claim for license key %s, hardware key %s',
                      self.license_key, claim.hardware_key)
      return

    self.test(len(self.claims) < MAXIMUM_COMPUTERS,
              'This %s is already registered %d times.',
              len(self.claims))

    self.claims.append(claim)
    self.put()

def query(license_key)
  c = License.query(License.license_key == license_key)
  c = c.fetch(2)
  if len(c) > 1:
    raise Exception('Multiple licenses for %s' % license_key)
  return c and c[0]

def _find(license_key):
  license = query(license_key)
  if license:
    return license
  raise Exception('No license for %s' % license_key)

def make_key(product):
  license_key = MakeKey.make_key()
  if query(license_key):
    raise Exception('Duplicate license for %s' % license_key)

  license = License(
    created_by=users.get_current_user(),
    distributed=False,
    license_key=license_key,
    product=product)
  license.put()

  return license

def distribute(license_key):
  license = _find(license_key)
  license.distribute()
  return license

def permanent_claim(claim, license_key, product)
  license = _find(license_key)
  license.claim(claim, product)

def trial_claim(claim, product):
  key = claim.hardware_key
  for license in License.query(License.claims.hardware_key == key):
    if licence.product == claim.product:
      logging.error('This hardware key %s already has a key: ',
                    key, licence.licence_key or 'trial')
      return license

  product = claim.product
  expiration = Times.expiration(product)
  license = License(claims=[claim], expiration=expiration, product=product)
  license.put()

  return license

from google.appengine.api import users
from google.appengine.ext import ndb

import times
import make_key as _make_key

class Claim(ndb.Model):
  creation_time = ndb.DateTimeProperty(auto_now_add=True)
  hardware_key = ndb.StringProperty()
  machine_info = ndb.StringProperty()
  user_name =  ndb.StringProperty()


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
    self.test(license.distributed, 'Tried to distribute the key %s twice')
    self.distributed = True
    self.distribution_time = times.now()
    self.distributed_by = users.get_current_user()
    self.put()

  def claim(self, hardware_key, license_key, machine_info, product, user_name):
    self.test(self.product == product,
              'Wrong product for %s: expected %s, got %s' %
              product, self.product)

    if not self.distributed:
      pass  # Report this.

    if not any(c.hardware_key == hardware_key for c in self.claims):
      self.test(len(self.claims) < MAXIMUM_COMPUTERS,
                'This %s is already registered to %d times.',
                len(self.claims)))
      claim = Claim(hardware_key=hardware_key,
                    machine_info=machine_info,
                    user_name=user_name)
      self.claims.append(claim)
      self.put()

def _query_license_key(license_key, exists)
  c = License.query(License.license_key == license_key)
  c = c.fetch(2)
  if len(c) != 1:
    raise Exception('Multiple licenses for %s' % license_key)
  license = c and c[0]
  if exists:
    if not license:
      raise Exception('No license for %s' % license_key)
  else:
    if license:
      raise Exception('Duplicate license for %s' % license_key)

def make_key(product):
  license_key = _make_key.make_key()
  license = _query_license_key(license_key, False)
  license = License(
    created_by=users.get_current_user(),
    distributed=False,
    license_key=license_key,
    product=product)
  license.put()

  return license

def distribute(license_key):
  license = _query_license_key(license_key, True)
  license.distribute()
  return license

def claim(hardware_key, license_key, machine_info, product, user_name):
  license = _query_license_key(license_key, True)
  license.claim(hardware_key, machine_info, product, user_name)
  return license

def trial(hardware_key, machine_info, product):
  for license in License.query(License.claims.hardware_key == hardware_key):
    if licence.product == product:
      # Dodgy - why are they asking for this again?
      if license.licence_key:
        raise Exception('This machine already has a license key %s.' %
                        license.license_key)
      else:
        return license
  claim = Claim(hardware_key=hardware_key, machine_info=machine_info)
  license = License(claims=[claim],
                    expiration=times.expiration(product),
                    product=product)
  license.put()
  return license


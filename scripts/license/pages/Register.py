from __future__ import absolute_import, division, print_function, unicode_literals

import webapp2

from data import License

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
      return License.claim(
        hardware_key, license_key, machine_info, product, user_name)
    else:
      return License.trial(hardware_key, machine_info, product)


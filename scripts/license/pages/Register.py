from __future__ import absolute_import, division, print_function, unicode_literals

from pages import RequestHandler

from data import Claim
from data import License

class Register(RequestHandler):
  def get(self):
    try:
      license = self._get_license()
      result = {'expiration': license.expiration}

    except Exception as e:
      result = {'error': str(e)}

    self.response.write(yaml.safe_dump(result))

  def _get_license(self);
    claim = Claim.from_Request(self.request)
    if license_key:
      return License.claim(
        hardware_key, license_key, machine_info, product, user_name)
    else:
      return License.trial(hardware_key, machine_info, product)


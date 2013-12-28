from google.appengine.ext import ndb

from data import License

class Claim(ndb.Model):
  creation_time = ndb.DateTimeProperty(auto_now_add=True)
  hardware_key = ndb.StringProperty()
  machine_info = ndb.StringProperty()
  user_name =  ndb.StringProperty()


def license(request):
  claim = Claim(
    hardware_key=request.get('hardware_key', ''),
    machine_info=request.get('machine_info', ''),
    user_name = request.get('user_name', ''))

  license_key = request.get('license_key', '')
  product = request.get('product', '')
  if license_key:
    return License.permanent_claim(claim, license_key, product)
  else:
    return License.trial_claim(claim, product)

from google.appengine.ext import ndb

class Claim(ndb.Model):
  creation_time = ndb.DateTimeProperty(auto_now_add=True)
  hardware_key = ndb.StringProperty()
  machine_info = ndb.StringProperty()
  user_name =  ndb.StringProperty()

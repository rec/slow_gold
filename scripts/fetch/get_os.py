#!/usr/local/bin/python

import platform

def get_os(platform_name=None):
  if (platform_name or platform.platform()).startswith('Darwin'):
    return 'mac'
  else:
    return 'windows'


OS = get_os()

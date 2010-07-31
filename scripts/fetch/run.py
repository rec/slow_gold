#!/usr/local/bin/python

import copy
import functools
import os
import subprocess


def run(*commands, **kwds):
  return [cmd(data.format(**kwds)) for cmd, data in commands]


def call(cmd, **env):
  error = subprocess.call(cmd.split(' '), env=env)
  if error:
    raise OSError, '{0}: "{1}"'.format(error, cmd)


def caller(**kwds):
  env = copy.copy(os.environ)
  env.update(**kwds)
  return functools.partial(call, **env)


#!/usr/local/bin/python

import flags
import run


def fetch():
  options, args = flags.parse()
  print options, args
  if True: return
  caller = run.caller()
  run.run(*((caller, options[i]) for i in args))


if __name__ == "__main__":
  fetch()

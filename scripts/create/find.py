#!/usr/local/bin/python

import os
import stat
import sys

def walktree (top = ".", depthfirst = True):
  names = os.listdir(top)
  if not depthfirst:
    yield top, names

  for name in names:
    try:
      st = os.lstat(os.path.join(top, name))
    except os.error:
      continue
    if stat.S_ISDIR(st.st_mode):
      for (newtop, children) in walktree (os.path.join(top, name), depthfirst):
        yield newtop, children

  if depthfirst:
    yield top, names

name = (sys.argv + ['/Users/tom/Documents/development/rec/scripts'])[1]

for t in [False, True]:
  print 'Walking', t
  if False:
    for f in walktree(name, t):
      print f
  else:
    print list(walktree(name, t))
  print

# for (basepath, children) in walktree(sys.argv[1], False):
#   for child in children:
#     print os.path.join(basepath, child)

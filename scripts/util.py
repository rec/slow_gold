import os

def pathParts(s):
  parts = os.path.abspath(s).split('/src/rec/')[1:]
  if not parts:
    raise ValueError(s)
  parts = ['rec'] + parts[0].split('/')
  parts[-1] = parts[-1].split('.')[0]

  if parts[-1] == 'base':
    parts.pop()

  return parts

def run(cmd):
  print '$', cmd
  os.system(cmd)


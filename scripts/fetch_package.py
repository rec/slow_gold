#!/usr/local/bin/python

import copy
import optparse
import os
import platform
import subprocess

def get_os():
  if platform.platform().startswith('Darwin'):
    return 'mac'
  else:
    return 'windows'

FLAGS = (
  ('name', {'help': 'This'}),
  ('version', {}),
  ('cwd', {'default': os.getcwd()}),
  ('os', {'default': get_os()}),
  ('suffix', {'default': '.tar.bz2'}),
  ('config_flags', {'default': '--with-cpu=x86  --enable-static --enable-shared=no'}),
  ('archive', {'default': '{directory}{suffix}'}),
  ('directory', {'default': '{name}-{version}'}),
  ('download', {'default': 'wget {url}'}),
  ('extract', {'default': 'tar xzf {archive}'}),
  ('url', {'default': 'http://{path}/{archive}'}),
  ('configure', {'default':  './configure {config_flags}'}),
  )

USAGE_MESSAGE = """Usage:
    fetch_package.py --name=NAME --value=VALUE [optional flags]

Type
    fetch_package.py --help
for more information on the optional flags."""


parser = optparse.OptionParser()
for name, keywords in FLAGS:
  parser.add_option('--' + name, dest=name, **keywords)

options, args = parser.parse_args()

if args:
  print USAGE_MESSAGE
  return -1

for name, value in options.iteritems():
  if not value:
    print USAGE_MESSAGE
    return -1

for name, value in FLAGS:
  options[name] = options[name].format(**options)

env = copy.copy(os.environ)
env['CC'] = 'gcc -arch i386'

for c in COMMANDS:
  error = subprocess.call(options[c].split(' '), env=env)
  if error:
    raise OSError, '{0}: "{1}"'.format(error, c)



class Getter:

  COMMANDS = ['{download}',
              '{extract}',
              'rm {filename}']

  def __init__(self, **keywords):
    self.variables = copy.copy(Getter.VARIABLES)
    for k, v in VARIABLES:
      self.variables[k] = self.variables.get(k, v).format(**self.variables)

  def commands(self, cmds=Getter.COMMANDS):
    return (self.variables[c] for c in cmds)

  def call(self, *commands):
    for c in commands:
      error = subprocess.call(c.split(' '))
      if error:
        raise OSError, '{0}: "{1}"'.format(error, c)


case "`uname`" in
  "Darwin" )
  OS=mac
  ;;

  * )
  OS=windows
  ;;
esac

export CC="gcc -arch i386"
INSTALL_PATH="`pwd`/lib/$OS"

./configure\
 --with-cpu=x86\
 --enable-static\
 --enable-shared=no\
 --prefix=$INSTALL_PATH/Release

make clean
make
make install

./configure\
 --with-cpu=x86\
 --enable-static\
 --enable-shared=no\
 --enable-debug\
 --prefix=$INSTALL_PATH/Debug

make
make clean
make install

cd ..
echo "Finished installing mpg123-$VERSION"

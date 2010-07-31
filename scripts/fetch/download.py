#!/usr/local/bin/python

import flags
import run

caller = run.caller(CC='gcc -arch i386')

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

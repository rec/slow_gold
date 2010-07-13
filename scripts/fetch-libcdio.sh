VERSION=0.82

wget http://ftp.gnu.org/gnu/libcdio/libcdio-$VERSION.tar.gz
tar xzf libcdio-$VERSION.tar.gz
rm libcdio-$VERSION.tar.gz

ln -s libcdio-$VERSION libcdio
cd libcdio

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
echo "Finished installing libcdio-$VERSION"

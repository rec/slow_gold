VERSION=1.12.1

wget http://sourceforge.net/projects/mpg123/files/mpg123/$VERSION/mpg123-$VERSION.tar.bz2/download
tar xzf mpg123-$VERSION.tar.bz2
rm mpg123-$VERSION.tar.bz2

ln -s mpg123-$VERSION mpg123
cd mpg123

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

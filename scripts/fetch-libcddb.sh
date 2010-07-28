VERSION=1.3.2

# wget http://prdownloads.sourceforge.net/libcddb/libcddb-$VERSION.tar.bz2
# tar xzf libcddb-$VERSION.tar.bz2
# rm libcddb-$VERSION.tar.bz2

# ln -s libcddb-$VERSION libcddb
cd libcddb

case "`uname`" in
  "Darwin" )
  OS=mac
  export CC="gcc -arch i386 -isysroot /Developer/SDKs/MacOSX10.5.sdk -mmacosx-version-min=10.5"
  ;;

  * )
  OS=windows
  export CC="gcc -arch i386"
  ;;
esac

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
echo "Finished installing libcddb-$VERSION"

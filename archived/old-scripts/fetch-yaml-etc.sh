VERSION=0.2.5

wget http://yaml-cpp.googlecode.com/files/yaml-cpp-0.2.5.tar.gz
tar xzf yaml-cpp-$VERSION.tar.gz
rm yaml-cpp-$VERSION.tar.gz

ln -s yaml-cpp-$VERSION yaml-cpp
cd yaml-cpp

case "`uname`" in
  "Darwin" )
  OS=mac
  ;;

  * )
  OS=windows
  ;;
esac

# Urg, not interested in putting all their BS here...
./bootstrap
make && sudio make install
sudo make install

#
wget http://yaml-cpp.googlecode.com/files/yaml-cpp-0.2.5.tar.gz
cmake .. -DCMAKE_SYSTEM_PROCESSOR=x86 -DBUILD_SHARED_LIBS=0 -DCMAKE_INSTALL_PREFIX=/Users/tom/Documents/development/yaml-cpp-0.2.5/Release -DCMAKE_VERBOSE_MAKEFILE=1 -DLIB_TYPE=STATIC

make && make install



export CC="gcc -arch i386"
INSTALL_PATH="`pwd`/lib/$OS"
mkdir -p $INSTALL_PATH/Release
mkdir -p $INSTALL_PATH/Debug

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

NAME=yaml-cpp
VERSION=0.2.5
ARCHIVE=$NAME-$VERSION.tar.gz
CONFIG=Release
PLATFORM=mac

# wget http://yaml-cpp.googlecode.com/files/$ARCHIVE
# tar xzf $ARCHIVE
# rm $ARCHIVE

# ln -s $NAME-$VERSION $NAME

INSTALL_DIR=`pwd`/build/$PLATFORM/$CONFIG/$NAME
mkdir -p $INSTALL_DIR
pushd $NAME

mkdir -p build
cd build
cmake .. -DCMAKE_SYSTEM_PROCESSOR=x86 -DBUILD_SHARED_LIBS=0 -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_VERBOSE_MAKEFILE=1 -DLIB_TYPE=STATIC
make && make install

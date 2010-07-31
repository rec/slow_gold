NAME=cmake
VERSION=2.8.2
ARCHIVE=$NAME-$VERSION.tar.gz
CONFIG=Release

wget http://www.cmake.org/files/v2.8/$ARCHIVE
tar xzf $ARCHIVE
rm $ARCHIVE

ln -s $NAME-$VERSION $NAME

INSTALL_DIR=`pwd`/build/$CONFIG/$NAME
mkdir -p $INSTALL_DIR
pushd $NAME

./bootstrap --prefix=$INSTALL_DIR &&\
 make &&\
 make install

popd
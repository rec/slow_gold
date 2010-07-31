NAME=cmake
VERSION=2.8.2

TMP=/tmp
EXTRACT=tar xzf
RM=rm
LN=ln -s
GET=wget
SUFFIX=.tar.gz

ARCHIVE=$NAME-$VERSION.tar.gz
$GET http://www.cmake.org/files/v2.8/$ARCHIVE

$EXTRACT $ARCHIVE

$RM $ARCHIVE

$LN -s $NAME-$VERSION $NAME

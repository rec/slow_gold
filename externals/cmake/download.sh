TMP=/tmp
RM=rm
LN=ln -s
GET=wget
SUFFIX=tar.gz
EXTRACT=tar xzf

NAME=cmake
VERSION=2.8.2

ARCHIVE=$NAME-$VERSION.$SUFFIX
$GET http://www.cmake.org/files/v2.8/$ARCHIVE

$EXTRACT $ARCHIVE

$RM $ARCHIVE

$LN -s $NAME-$VERSION $NAME

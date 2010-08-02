TMP="/tmp"
RM="rm"
LN="ln -s"
GET="wget"
SUFFIX="tar.gz"
EXTRACT="tar xzf"
CONFIGURE="./configure"
CONFIGURE_FLAGS="--with-cpu=x86 --enable-static --enable-shared=no"
PREFIX_FLAG="--prefix"
MAKE_INSTALL="make clean && make && make install"
CC_BASE="gcc -arch i136"

source rec/scripts/platform/platform.sh
source rec/scripts/package/$PACKAGE.sh

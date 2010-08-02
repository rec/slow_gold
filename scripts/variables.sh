TMP=/tmp
RM=rm
LN="ln -s"
GET=wget
SUFFIX=tar.gz
EXTRACT="tar xzf"
CONFIGURE="./configure"
CONFIGURE_FLAGS="--with-cpu=x86 --enable-static --enable-shared=no"
PREFIX_FLAG="--prefix"
MAKE="make clean && make && make install"

source rec/scripts/platform.sh
source rec/scripts/platforms/$PLATFORM.sh
source rec/scripts/packages/$PACKAGE.sh

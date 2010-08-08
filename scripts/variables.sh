SUFFIX="tar.bz2"
CONFIGURE="./configure --enable-static --enable-shared=no"
CONFIGURE_CPU_FLAG="--with-cpu=x86"
PREFIX_FLAG="--prefix"
CPPFLAGS="-arch i386"
CONFIGURE_SCRIPT="standard"
ROOT="`pwd`"
SCRIPTS="$ROOT/rec/scripts"

source "$SCRIPTS/platform/platform.sh" &&\
  source "$SCRIPTS/config/$CONFIG.sh" &&\
  source "$SCRIPTS/package/$PACKAGE.sh"

INSTALL_DIR="$ROOT/build/$PLATFORM/$CONFIG/$PACKAGE"


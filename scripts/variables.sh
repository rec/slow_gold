SUFFIX="tar.bz2"
CONFIGURE="./configure --enable-static --enable-shared=no"
CONFIGURE_CPU_FLAG="--with-cpu=x86"
PREFIX_FLAG="--prefix"
CPPFLAGS="-arch i386"
CONFIGURE_SCRIPT="standard"

source rec/scripts/platform/platform.sh

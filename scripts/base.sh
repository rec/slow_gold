SUFFIX="tar.bz2"
CONFIGURE="./configure --enable-static --enable-shared=no"
CONFIGURE_CPU_FLAG="--with-cpu=x86"
PREFIX_FLAG="--prefix"
CPPFLAGS="-arch i386"
CONFIGURE_SCRIPT="standard"
PACKAGES="gflags glog gtest libcddb mpg123 protobuf"
CONFIG_PACKAGES=$PACKAGES
TAR_ARGS="xjf"
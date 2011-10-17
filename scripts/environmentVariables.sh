# For some reason I don't understand, blank lines in this file give errors in
# the output...
#
CONFIGURE="./configure --enable-static --enable-shared=no"
CONFIGURE_CPU_FLAG="--with-cpu=x86"
CONFIGURE_SCRIPT="standard"
CPPFLAGS="-arch i386"
DOWNLOAD="curl -O"
PACKAGES="gflags glog gtest mpg123 protobuf rubberband soundtouch"
PREFIX_FLAG="--prefix"
SUFFIX="tar.bz2"
EXTRACT="tar xjf"
PROJECTS="slow tests command"
JUCER="Jucer"
#
CONFIG_PACKAGES="$PACKAGES"

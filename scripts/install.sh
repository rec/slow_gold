PACKAGE=$1
CONFIG=$2

source variables.sh

INSTALL_DIR=`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE
mkdir -p $INSTALL_DIR
pushd $INSTALL_DIR

source packages/$PACKAGE/build.sh

popd


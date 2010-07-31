PACKAGE=$1
$CONFIG=$2

INSTALL_DIR=`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE
mkdir -p $INSTALL_DIR

pushd $INSTALL_DIR

source externals/$PACKAGE/build.sh

popd


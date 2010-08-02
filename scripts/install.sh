PACKAGE=$1
CONFIG=$2

source rec/scripts/variables.sh

INSTALL_DIR=`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE
SCRIPT_DIR=`pwd`/rec/scripts

mkdir -p $INSTALL_DIR
pushd $PACKAGE

source $SCRIPT_DIR/packages/$PACKAGE/install.sh

popd


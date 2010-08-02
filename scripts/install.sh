PACKAGE=$1
CONFIG=$2

source rec/scripts/variables.sh

INSTALL_DIR="`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE"
SCRIPT_DIR="`pwd`/rec/scripts"

mkdir -p "$INSTALL_DIR"
pushd $PACKAGE

export CC="$CC_BASE $EXTRA_CC_FLAGS"

$CONFIGURE $CONFIGURE_FLAGS $PREFIX_FLAG=$INSTALL_DIR &&\
 $MAKE_INSTALL

popd


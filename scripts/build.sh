CONFIG=$1

shift

while (( "$#" )); do
  PACKAGE=$1

  source rec/scripts/variables.sh
  source rec/scripts/config/$CONFIG.sh
  source rec/scripts/package/$PACKAGE.sh

  INSTALL_DIR="`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE"
  SCRIPT_DIR="`pwd`/rec/scripts"

  mkdir -p "$INSTALL_DIR"
  pushd $PACKAGE
  export CFLAGS=$CFLAGS

  $CONFIGURE\
     $CONFIGURE_FLAGS\
     $EXTRA_CONFIGURE_FLAGS\
     $PREFIX_FLAG=$INSTALL_DIR &&\
   $MAKE_CLEAN &&\
   $MAKE_ALL &&\
   $MAKE_INSTALL

  popd
  shift
done


CONFIG=$1
shift

SCRIPTS="`pwd`/rec/scripts"

while (( "$#" )); do
  PACKAGE=$1
  shift

  source $SCRIPTS/variables.sh
  source $SCRIPTS/config/$CONFIG.sh
  source $SCRIPTS/package/$PACKAGE.sh

  INSTALL_DIR="`pwd`/build/$PLATFORM/$CONFIG/$PACKAGE"
  mkdir -p "$INSTALL_DIR"

  pushd $PACKAGE

  source $SCRIPTS/configure.sh &&\
   source $SCRIPTS/make.sh

  popd

done


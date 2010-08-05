CONFIG=$1
shift

ROOT="`pwd`"
SCRIPTS="$ROOT/rec/scripts"

while (( "$#" )); do
  PACKAGE=$1
  shift

  cd $ROOT
  source $SCRIPTS/variables.sh
  source $SCRIPTS/config/$CONFIG.sh
  source $SCRIPTS/package/$PACKAGE.sh

  INSTALL_DIR="$ROOT/build/$PLATFORM/$CONFIG/$PACKAGE"
  if [ -d "$INSTALL_DIR" ] ; then
    echo "Removing $INSTALL_DIR"
    rm -Rf "$INSTALL_DIR"
  fi

  echo "Creating $INSTALL_DIR"
  mkdir -p "$INSTALL_DIR"

  echo "Building package $PACKAGE, config=$CONFIG into $INSTALL_DIR"
  cd $ROOT/$PACKAGE
  source $SCRIPTS/configure.sh &&
   make clean &&\
   make &&\
   make install

done

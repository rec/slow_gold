CONFIG=$1
shift

while (( "$#" )); do
  PACKAGE="$1"
  shift

  cd "$ROOT"
  source "rec/scripts/variables.sh"

  if [ -d "$INSTALL_DIR" ] ; then
    echo "Removing $INSTALL_DIR"
    rm -Rf "$INSTALL_DIR"
  fi

  echo "Creating $INSTALL_DIR"
  mkdir -p "$INSTALL_DIR"

  echo "Building package $PACKAGE, config=$CONFIG into $INSTALL_DIR"
  cd "$ROOT/$PACKAGE"
  source "$SCRIPTS/configure.sh"
  make clean
  make
  make install

done

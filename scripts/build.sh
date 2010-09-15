source "$ROOT/rec/scripts/base.sh"

CONFIG=$1
shift
if [ ! "$CONFIG" ]; then
  CONFIG=debug
fi

if [ ! "$@" ]
then

  "$ROOT/rec/scripts/build.sh" $CONFIG $PACKAGES

else

  while (( "$#" )); do
    PACKAGE="$1"
    shift
    echo
    echo
    echo "       *** building $PACKAGE ***"
    echo
    echo

    cd "$ROOT"
    source "rec/scripts/variables.sh"

    if [ -d "$INSTALL_DIR" ] ; then
      echo "Removing $INSTALL_DIR"
      rm -Rf "$INSTALL_DIR"
    fi

    echo "Creating $INSTALL_DIR"
    mkdir -p "$INSTALL_DIR"

    echo "  ===== BUILDING ===== $PACKAGE, config $CONFIG, on $PLATFORM, into $INSTALL_DIR"
    cd "$ROOT/$PACKAGE"
    source "$ROOT/rec/scripts/configure.sh"
    make clean
    make
    make install

  done

fi
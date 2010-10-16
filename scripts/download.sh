# Download the packages given as arguments

CONFIG=debug

cd "$ROOT"
source "$ROOT/rec/scripts/base.sh"

if [ ! "$1" ]
then

  "$ROOT/rec/scripts/download.sh" $CONFIG_PACKAGES

else

  while (( "$#" )); do

    PACKAGE=$1
    shift
    echo
    echo
    echo "       *** Downloading $PACKAGE ***"
    echo
    echo

    source "$ROOT/rec/scripts/variables.sh"
    source "$ROOT/rec/scripts/package/$PACKAGE.sh"

    ARCHIVE="$PACKAGE-$VERSION.$SUFFIX"

    curl -O "$URL_PATH/$ARCHIVE"
    tar "$TAR_ARGS" "$ARCHIVE"
    rm "$ARCHIVE"
    ln -s "$PACKAGE-$VERSION" "$PACKAGE"

  done

fi
# Download the packages given as arguments

CONFIG=debug

cd "$ROOT"
source "$ROOT/rec/scripts/base.sh"

if [ ! "$1" ]
then

  "$ROOT/rec/scripts/download.sh" $PACKAGES

else

  while (( "$#" )); do

    PACKAGE=$1
    shift

    source "$ROOT/rec/scripts/variables.sh"
    source "$ROOT/rec/scripts/package/$PACKAGE.sh"

    ARCHIVE="$PACKAGE-$VERSION.$SUFFIX"
    ARCHIVE_PATH="$URL_PATH/$ARCHIVE"

    echo
    echo
    echo "       *** Downloading $PACKAGE from $URL_PATH/$ARCHIVE ***"
    echo
    echo

    curl -O "$ARCHIVE_PATH"
    tar "$TAR_ARGS" "$ARCHIVE"
    rm "$ARCHIVE"
    if [ -f "$PACKAGE" ]; then
      mv -f "$PACKAGE" "$PACKAGE.old"
    fi
    mv "$PACKAGE-$VERSION" "$PACKAGE"

  done

fi
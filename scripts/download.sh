# Download the packages given as arguments
CONFIG=debug

source "$ROOT/rec/scripts/base.sh"

if [ ! "$@" ]
then

  "$ROOT/rec/scripts/download.sh" $PACKAGES

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

    ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

    curl -O $URL_PATH/$ARCHIVE
    tar xjf $ARCHIVE
    rm $ARCHIVE
    ln -s $PACKAGE-$VERSION $PACKAGE

  done

fi
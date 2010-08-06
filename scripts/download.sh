# Download the packages given as arguments

CONFIG=debug

while (( "$#" )); do

  PACKAGE=$1
  shift

  source rec/scripts/variables.sh
  source rec/scripts/package/$PACKAGE.sh

  ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

  curl -O $URL_PATH/$ARCHIVE &&\
   tar xzf $ARCHIVE &&\
   rm $ARCHIVE &&\
   ln -s $PACKAGE-$VERSION $PACKAGE

done
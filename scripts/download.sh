# Our generic download program!

while (( "$#" )); do
  PACKAGE=$1

  source rec/scripts/variables.sh
  source rec/scripts/package/$PACKAGE.sh

  ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

  curl -O $URL_PATH/$ARCHIVE$ARCHIVE_END &&\
   $EXTRACT $ARCHIVE &&\
   $RM $ARCHIVE &&\
   $LN $PACKAGE-$VERSION $PACKAGE

  shift
done
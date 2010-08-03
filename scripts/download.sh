# Our generic download program!

echo "HERE!!!"
while (( "$#" )); do
  PACKAGE=$1

  source rec/scripts/variables.sh
  source rec/scripts/package/$PACKAGE.sh

  ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

  echo "curl -O $URL_PATH/$ARCHIVE$ARCHIVE_END &&"
  curl -O $URL_PATH/$ARCHIVE$ARCHIVE_END &&\
   $EXTRACT $ARCHIVE &&\
   $RM $ARCHIVE &&\
   $LN $PACKAGE-$VERSION $PACKAGE

  shift
done
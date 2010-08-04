# Our generic download program!

<<<<<<< HEAD:scripts/download.sh
=======
echo "HERE!!!"
>>>>>>> 3040847d8c967735f094d5f0ae9eb27763875ec9:scripts/download.sh
while (( "$#" )); do
  PACKAGE=$1

  source rec/scripts/variables.sh
<<<<<<< HEAD:scripts/download.sh

  ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

  $GET $URL_PATH/$ARCHIVE$ARCHIVE_END &&\
=======
  source rec/scripts/package/$PACKAGE.sh

  ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

  echo "curl -O $URL_PATH/$ARCHIVE$ARCHIVE_END &&"
  curl -O $URL_PATH/$ARCHIVE$ARCHIVE_END &&\
>>>>>>> 3040847d8c967735f094d5f0ae9eb27763875ec9:scripts/download.sh
   $EXTRACT $ARCHIVE &&\
   $RM $ARCHIVE &&\
   $LN $PACKAGE-$VERSION $PACKAGE

  shift
done
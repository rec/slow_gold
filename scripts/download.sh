# Our generic download program!

PACKAGE=$1

source rec/scripts/variables.sh

ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

$GET $URL_PATH/$ARCHIVE$ARCHIVE_END &&\
 $EXTRACT $ARCHIVE &&\
 $RM $ARCHIVE &&\
 $LN $PACKAGE-$VERSION $PACKAGE

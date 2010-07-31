# Our generic download program!

PACKAGE=$1

source variables.sh

ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

$GET $URL_PATH/$ARCHIVE &&\
 $EXTRACT $ARCHIVE &&\
 $RM $ARCHIVE &&\
 $LN $PACKAGE-$VERSION $PACKAGE

# Our generic download program!

PACKAGE=$1

source rec/scripts/platform.sh
source rec/scripts/externals/variables.sh
source rec/scripts/platforms/$PLATFORM/variables.sh
source rec/scripts/externals/$PACKAGE/variables.sh

ARCHIVE=$PACKAGE-$VERSION.$SUFFIX

$GET $URL_PATH/$ARCHIVE &&\
 $EXTRACT $ARCHIVE &&\
 $RM $ARCHIVE &&\
 $LN $PACKAGE-$VERSION $PACKAGE

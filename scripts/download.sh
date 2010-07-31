# Our generic download program!

PACKAGE=$1

source scripts/platform.sh

source externals/variables.sh
source platforms/$PLATFORM/variables.sh
source externals/$PACKAGE/variables.sh

$GET $URL_PATH/$ARCHIVE
$EXTRACT $ARCHIVE
$RM $ARCHIVE
$LN $NAME-$VERSION $NAME

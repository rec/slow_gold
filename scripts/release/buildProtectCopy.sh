VERSION=${1:-8.0.2}

SCRIPTS=/development/rec/scripts

$SCRIPTS/compileCode.sh Release && \
 $SCRIPTS/protectCopy.sh $VERSION

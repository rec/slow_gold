source "$ROOT/rec/scripts/environmentVariables.sh" &&\
 source "$ROOT/rec/scripts/platform/platform.sh" &&\
 source "$ROOT/rec/scripts/config/$CONFIG.sh" &&\
 source "$ROOT/rec/scripts/package/$PACKAGE.sh"

INSTALL_DIR="$ROOT/build/$CONFIG/$PACKAGE"
source "$ROOT/rec/scripts/base.sh" &&\
 source "$ROOT/rec/scripts/platform/platform.sh" &&\
 source "$ROOT/rec/scripts/config/$CONFIG.sh" &&\
 source "$ROOT/rec/scripts/package/$PACKAGE.sh"

INSTALL_DIR="$ROOT/build/$CONFIG/$PACKAGE"
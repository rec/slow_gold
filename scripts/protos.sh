PACKAGE=protobuf
CONFIG=debug
# ROOT="`pwd`"

source "$ROOT/rec/scripts/variables.sh"

PROTO_ROOT="$ROOT/rec/genfiles/proto"
SRC_ROOT="$ROOT/rec/src"
mkdir -p "$PROTO_ROOT"
find "$PROTO_ROOT" -name \*.pb.\* | xargs rm
find "$SRC_ROOT" -name \*.proto |\
 xargs "$INSTALL_DIR/bin/protoc" -I"$SRC_ROOT" -I"$ROOT/build/$PLATFORM/$CONFIG/protobuf/include"  --cpp_out="$PROTO_ROOT"



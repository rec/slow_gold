PACKAGE=protobuf
CONFIG=debug

source "$ROOT/rec/scripts/variables.sh"

SRC_ROOT="$ROOT/rec/src"
PROTO_ROOT="$ROOT/rec/genfiles/proto"

$INSTALL_DIR/bin/protoc \
  -I "$SRC_ROOT"\
  -I "$ROOT/build/$CONFIG/protobuf/include" \
  --cpp_out="$PROTO_ROOT" \
  --python_out="$PROTO_ROOT" \
  "$SRC_ROOT"/$1
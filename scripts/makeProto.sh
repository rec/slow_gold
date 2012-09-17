PACKAGE=protobuf
CONFIG=debug

source "$ROOT/rec/scripts/variables.sh"


SRC_ROOT="$ROOT/rec/src"
PROTO_ROOT="$ROOT/rec/genfiles/proto"


 echo "$INSTALL_DIR/bin/protoc \
   -I \"$SRC_ROOT\"\
   -I \"$INSTALL_DIR/include\" \
   --cpp_out=\"$PROTO_ROOT\" \
   --python_out=\"$PROTO_ROOT\" \
   \"$SRC_ROOT\"/$@"

echo "Creating $@"

$INSTALL_DIR/bin/protoc \
  -I "$SRC_ROOT"\
  -I "$INSTALL_DIR/include" \
  --python_out="$PROTO_ROOT" \
  --cpp_out="$PROTO_ROOT" \
  $@

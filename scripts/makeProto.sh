PACKAGE=protobuf
CONFIG=debug

source "$ROOT/rec/scripts/variables.sh"

SRC_ROOT="$ROOT/rec/src"
PROTO_ROOT="$ROOT/rec/genfiles/proto"

if [ "" ]
then
  echo "$INSTALL_DIR/bin/protoc \
     -I \"$SRC_ROOT\"\
     -I \"$INSTALL_DIR/include\" \
     --cpp_out=\"$PROTO_ROOT\" \
     --python_out=\"$PROTO_ROOT\" \
     /$@"
  echo "Creating $@"
fi

$ROOT/rec/externals/mac/protobuf/bin/protoc \
  -I "$SRC_ROOT"\
  -I "$INSTALL_DIR/include" \
  --python_out="$PROTO_ROOT" \
  --cpp_out="$PROTO_ROOT" \
  $@

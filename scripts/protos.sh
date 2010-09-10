PACKAGE=protobuf
CONFIG=debug
# ROOT="`pwd`"

source "$ROOT/rec/scripts/variables.sh"

cd "$ROOT/rec/src"
"$INSTALL_DIR/bin/protoc" --cpp_out="$ROOT/rec/genfiles/proto" rec/*/*.proto rec/*/*/*.proto



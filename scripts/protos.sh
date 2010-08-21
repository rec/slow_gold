PACKAGE=protobuf
CONFIG=debug
ROOT="`pwd`"

source "$ROOT/rec/scripts/variables.sh"

cd rec/src
"$INSTALL_DIR/bin/protoc" --cpp_out=. rec/*/*.proto rec/*/*/*.proto
cd "$ROOT"


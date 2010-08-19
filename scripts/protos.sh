PACKAGE=protobuf
CONFIG=debug
ROOT="`pwd`"

source "$ROOT/rec/scripts/variables.sh"

find rec/src -name *.proto\
 -execdir "$INSTALL_DIR/bin/protoc" {} --cpp_out=. -I$ROOT/rec/src -I. \;

# --proto_path="$ROOT/rec/src"\
# --proto_path="$ROOT/rec/src/audio/stretch"\
# \;

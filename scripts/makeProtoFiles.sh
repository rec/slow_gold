PACKAGE=protobuf
CONFIG=debug

source "$ROOT/rec/scripts/variables.sh"

SRC_ROOT="$ROOT/rec/src"
PROTO_ROOT="$ROOT/rec/genfiles/proto"

mkdir -p "$PROTO_ROOT"
echo "Deleting `find "$PROTO_ROOT" -name \*.pb.\* | wc -l` compiled files."
echo "Deleting `find "$PROTO_ROOT" -name \*_pb2.py | wc -l` compiled files."

find "$PROTO_ROOT" -name \*.pb.\* | xargs rm
find "$SRC_ROOT" -name \*.proto | xargs "$ROOT/rec/scripts/makeProto.sh"
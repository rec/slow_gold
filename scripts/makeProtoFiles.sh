PACKAGE=protobuf
CONFIG=debug

source "$ROOT/rec/scripts/variables.sh"

SRC_ROOT="$ROOT"
PROTO_ROOT="$ROOT/rec/genfiles/proto"

mkdir -p "$PROTO_ROOT"
echo "Deleting `find "$PROTO_ROOT" -name \*.pb.\* | wc -l` compiled files."
echo "Deleting `find "$PROTO_ROOT" -name \*_pb2.py | wc -l` compiled py files."

find "$PROTO_ROOT" -name \*.pb.\* | xargs rm
find "$PROTO_ROOT" -name \*.pb2.py | xargs rm

find "$ROOT/rec/src/rec" -name \*.proto | xargs echo
find "$ROOT/rec/src/rec" -name \*.proto | xargs "$ROOT/rec/scripts/makeProto.sh"
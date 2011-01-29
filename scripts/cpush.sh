echo "pushd \"$ROOT/rec\" && git add . && git commit -am \"$1\" && git push origin main"
pushd "$ROOT/rec" && git add . && git commit -am "$1" && git push origin main
popd
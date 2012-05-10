VERSION=${1:-8.0.2}

GOOGLE_DRIVE="/Users/tom/Google Drive/woodshed/SlowGold/$VERSION/"
BIN_PATH=/development/rec/projects/slow/Builds/MacOSX/build/Release
APP_PATH="$BIN_PATH/SlowGold $VERSION"

cp "$BIN_PATH"/*.zip "$GOOGLE_DRIVE"
ROOT=/development/rec/projects/slow/Builds/MacOSX
CONFIG=Release
VERSION=8.2.0

BUILD_DIR=build/$CONFIG

BINARY=$BUILD_DIR/SlowGold\ 8.app
VERSION_BINARY=$BUILD_DIR/SlowGold\ $VERSION.app

cd $ROOT && \
    xcodebuild -project SlowGold.xcodeproj -configuration $CONFIG && \
    rm -Rf "$VERSION_BINARY" && \
    cp -R "$BINARY" "$VERSION_BINARY" && \
    zip -r "$VERSION_BINARY.zip" "$VERSION_BINARY" && \
    open $BUILD_DIR

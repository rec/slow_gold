ROOT=/development/rec/projects/slow/Builds/MacOSX
CONFIG=Debug
VERSION=8.1.1

BUILD_DIR=build/$CONFIG

BINARY=$BUILD_DIR/SlowGold\ 8.app
VERSION_BINARY=$BUILD_DIR/SlowGold\ $VERSION.app

cd $ROOT && \
    /development/checker-279/bin/scan-build xcodebuild -project SlowGold.xcodeproj -configuration $CONFIG && \
    rm -Rf "$VERSION_BINARY" && \
    cp -R "$BINARY" "$VERSION_BINARY" && \
    zip -r "$VERSION_BINARY.zip" "$VERSION_BINARY" && \
    open $BUILD_DIR

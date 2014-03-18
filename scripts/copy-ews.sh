#!/bin/bash

FRAMEWORKS="$TARGET_BUILD_DIR/SlowGold 8.app/Contents/Frameworks"
echo "Making directory $FRAMEWORKS"
mkdir -p "$FRAMEWORKS"
rm -Rf "$FRAMEWORKS/EWSEmbedded-GC.framework"
cp -Rfp ../../../../externals/mac/ews/EWSEmbedded-GC.framework "$FRAMEWORKS"

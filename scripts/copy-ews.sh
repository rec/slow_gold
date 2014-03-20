#!/bin/bash

FRAMEWORKS="$TARGET_BUILD_DIR/$FULL_PRODUCT_NAME/Contents/Frameworks"
echo "Making directory $FRAMEWORKS"
mkdir -p "$FRAMEWORKS"
rm -Rf "$FRAMEWORKS/EWSEmbedded-GC.framework"
pwd
env
cp -Rfp ../../../../externals/mac/ews/EWSEmbedded-GC.framework "$FRAMEWORKS"

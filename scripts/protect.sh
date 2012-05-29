VERSION=${1:-8.0.2}

BIN_PATH=/development/rec/projects/slow/Builds/MacOSX/build/Release
APP_PATH="SlowGold $VERSION"
ZIP_PATH="SlowGold-$VERSION"
POST_APP_PATH="${APP_PATH}_PreARM"
EXTENSION=app
ARM_FILE=/development/rec/projects/slow/SlowGold.mac.arm

doZip () {
  local VARIANT=$1
  local ZIP_FILE="$ZIP_PATH-$VARIANT.zip"
  cd "$BIN_PATH" && \
    rm -f "$ZIP_FILE" && \
    zip -qry9 "$ZIP_FILE" "$APP_PATH.$EXTENSION"/*
  echo "Created $BIN_PATH/$ZIP_FILE"
}

protect() {
  local VARIANT=$1
  local PASSPORT=$2

  $PASSPORT $ARM_FILE && \
   doZip $VARIANT && \
   rm -Rf "$APP_PATH.$EXTENSION" && \
   mv "$POST_APP_PATH.$EXTENSION" "$APP_PATH.$EXTENSION"
}

NEW_PASSPORT=/Applications/SoftwarePassport.new.app/Contents/MacOS/Modules/ArmCLine
OLD_PASSPORT=/Applications/SoftwarePassport.old.app/Contents/MacOS/Modules/ArmCLine

doZip mac-PreARM && \
  protect "mac-10.5" $OLD_PASSPORT && \
  protect mac $NEW_PASSPORT

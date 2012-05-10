VERSION=${1:-8.0.2}

NEW_PASSPORT=/Applications/SoftwarePassport.new.app/Contents/MacOS/Modules/ArmCLine
OLD_PASSPORT=/Applications/SoftwarePassport.old.app/Contents/MacOS/Modules/ArmCLine

ARM_FILE=/development/rec/projects/slow/SlowGold.mac.arm
BIN_PATH=/development/rec/projects/slow/Builds/MacOSX/build/Release
APP_PATH="$BIN_PATH/SlowGold $VERSION"
POST_APP_PATH="$APP_PATH"_PreARM
ZIP="zip -qry9"

rm -f "$APP_PATH"*.zip && \
 $ZIP "$APP_PATH"-mac-pre.zip "$APP_PATH.app" && \
 $NEW_PASSPORT $ARM_FILE && \
 $ZIP "$APP_PATH"-mac.zip "$APP_PATH.app" && \
 rm -Rf "$APP_PATH.app" && \
 mv "$POST_APP_PATH.app" "$APP_PATH.app" && \
 $OLD_PASSPORT $ARM_FILE && \
 $ZIP "$APP_PATH"-mac-10.5.zip "$APP_PATH.app" && \
 rm -Rf "$APP_PATH.app" && \
 mv "$POST_APP_PATH.app" "$APP_PATH.app"

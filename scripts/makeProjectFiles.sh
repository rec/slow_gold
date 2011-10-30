("$ROOT/rec/scripts/jucer/build_jucer_files.py" $PROJECTS &&\
\
 ICON_SOURCE="$ROOT/rec/art/icons" &&\
 ICON_MAC="$ROOT/rec/projects/slow/Builds/MacOSX" &&\
 ICON_WINDOWS="$ROOT/rec/projects/slow/Builds/VisualStudio2010" &&\
\
 mkdir -p "$ICON_MAC" "$ICON_WINDOWS" &&\
\
 cp -p "$ICON_SOURCE/SampleIconMac.icns" "$ICON_MAC/Icon.icns" &&\
 cp -p "$ICON_SOURCE/SampleIconWindows.ico" "$ICON_WINDOWS/icon.ico" &&\
\
 $ROOT/rec/scripts/runJucer.sh tests &&\
 $ROOT/rec/scripts/runJucer.sh slow &&\
 $ROOT/rec/scripts/runJucer.sh command &&\
\
 cp -p "$ICON_SOURCE/SampleIconMac.icns" "$ICON_MAC/Icon.icns" &&\
 cp -p "$ICON_SOURCE/SampleIconWindows.ico" "$ICON_WINDOWS/icon.ico"\
)

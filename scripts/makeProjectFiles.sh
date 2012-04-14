("$ROOT/rec/scripts/jucer/build_jucer_files.py" slow tests &&\
\
 ICON_MAC="$ROOT/rec/projects/slow/Builds/MacOSX" &&\
 ICON_WINDOWS="$ROOT/rec/projects/slow/Builds/VisualStudio2010" &&\
\
 mkdir -p "$ICON_MAC" "$ICON_WINDOWS" &&\
\
 $ROOT/rec/scripts/runJucer.sh slow &&\
 $ROOT/rec/scripts/runJucer.sh tests
)

# $ROOT/rec/scripts/runJucer.sh tests &&\
# $ROOT/rec/scripts/runJucer.sh command \

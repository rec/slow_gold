"$ROOT/rec/scripts/jucer/build_jucer_files.py" && \
 Jucer --resave $ROOT/rec/projects/tests/tests.jucer > /tmp/tests.jucer.log &&\
 Jucer --resave $ROOT/rec/projects/slow/slow.jucer  > /tmp/slow.jucer.log &&\
 cp -p $ROOT/rec/art/icons/SampleIconMac.icns ~/Documents/development/rec/projects/slow/Builds/MacOSX/Icon.icns &&\
 cp -p $ROOT/rec/art/icons/SampleIconWindows.ico ~/Documents/development/rec/projects/slow/Builds/VisualStudio2008/icon.ico


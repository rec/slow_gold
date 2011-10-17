NAME=$1

"/development/juce/extras/Introjucer/Builds/MacOSX/build/Debug/Introjucer.app/Contents/MacOS/IntroJucer" --resave "$ROOT/rec/projects/$NAME/$NAME.jucer" > "/tmp/$NAME.jucer.log" && \
 touch -t 201101010000 "$ROOT/rec/projects/$NAME/JuceLibraryCode/"Juce*

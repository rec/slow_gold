NAME=$1

"/Users/tom/Documents/development/juce/extras/the jucer/build/mac/build/Debug/Jucer.app" --resave "$ROOT/rec/projects/$NAME/$NAME.jucer" > "/tmp/$NAME.jucer.log" && \
 touch -t 201101010000 "$ROOT/rec/projects/$NAME/JuceLibraryCode/"Juce*

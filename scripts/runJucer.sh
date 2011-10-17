NAME=$1

"$JUCER" --resave "$ROOT/rec/projects/$NAME/$NAME.jucer" > "/tmp/$NAME.jucer.log" && \
 touch -t 201101010000 "$ROOT/rec/projects/$NAME/JuceLibraryCode/"Juce*

NAME=$1

PLATFORM=`uname`

if [[ $PLATFORM == CYGWIN* ]]
then
    INTROJUCER_APP="/apps/juce/extras/Introjucer/Builds/VisualStudio2010/Release/IntroJucer.exe"
else
    INTROJUCER_APP="/development/juce/extras/Introjucer/Builds/MacOSX/build/Release/Introjucer.app/Contents/MacOS/Introjucer"
fi

${INTROJUCER_APP} --resave "$ROOT/rec/projects/$NAME/$NAME.jucer" > "/tmp/$NAME.jucer.log" && \
 touch -t 201101010000 "$ROOT/rec/projects/$NAME/JuceLibraryCode/"Juce*

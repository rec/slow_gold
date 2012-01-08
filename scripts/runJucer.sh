NAME=$1

PLATFORM=`uname`

if [[ $PLATFORM == CYGWIN* ]] 
then
    INTROJUCER_APP="/apps/juce/extras/Introjucer/Builds/VisualStudio2010/Release/IntroJucer.exe"
else    
    INTROJUCER_APP="/development/juce/extras/Introjucer/Builds/MacOSX/build/Debug/Introjucer.app/Contents/MacOS/IntroJucer"
fi

${INTROJUCER_APP} --resave "$ROOT/rec/projects/$NAME/$NAME.jucer" > "/tmp/$NAME.jucer.log" && \
 touch -t 201101010000 "$ROOT/rec/projects/$NAME/JuceLibraryCode/"Juce*

INTROJUCER_APP=/development/juce/extras/Introjucer/Builds/MacOSX/build/Release/Introjucer.app/Contents/MacOS/Introjucer

PROJECT=slow
JUCE_PROJECT=/development/rec/projects/$PROJECT/$PROJECT.jucer

${INTROJUCER_APP} --resave-resources $JUCE_PROJECT > /tmp/$PROJECT.jucer.log



# cd /development/rec/projects/slow/Builds/MacOSX &&\
# xcodebuild -project SlowGold.xcodeproj -configuration Debug

# open /development/rec/projects/$PROJECT/Builds/MacOSX/SlowGold.xcodeproj/ &&\

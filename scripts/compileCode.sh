cd /development/rec/src/rec/slow/commands \
 && make \
 && cd /development/rec/projects/slow/Builds/MacOSX \
 && xcodebuild -project "SlowGold.xcodeproj" -configuration ${1:-Debug}
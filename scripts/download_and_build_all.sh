PACKAGES="gflags glog gtest libcddb mpg123 protobuf"
CONFIG=debug

source rec/scripts/download.sh $PACKAGES &&\
 source rec/scripts/build.sh $CONFIG $PACKAGES &&\
 open rec/projects/tests/Builds/MacOSX/tests.xcodeproj &&\
 open rec/projects/slow/Builds/MacOSX/Slow.xcodeproj
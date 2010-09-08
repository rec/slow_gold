
cd rec/src
find . \( -name \*.h -or -name \*.cpp \) | xargs etags
exit -1


# older stuff starts here just for the record.
CONFIG=$1
if [[ "$CONFIG" == "" ]]
then CONFIG=debug
fi

source "rec/scripts/platform/platform.sh"

#  "build/$PLATFORM/$CONFIG"


find rec/src \( -name \*.h -or -name \*.cpp \) | xargs etags > rec/TAGS
echo "done."

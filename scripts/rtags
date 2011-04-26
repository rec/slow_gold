
cd "$ROOT/rec/src"
find . \( -name \*.h -or -name \*.cpp \) | xargs etags
echo "TAGS table written."
exit -1


# older stuff starts here just for the record.
CONFIG=$1
if [[ "$CONFIG" == "" ]]
then CONFIG=debug
fi

source "rec/scripts/platform/platform.sh"

find rec/src \( -name \*.h -or -name \*.cpp \) | xargs etags > rec/TAGS

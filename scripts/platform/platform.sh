# Get our name for the current

PLATFORM=other

case "`uname`" in

  "Darwin" )
  PLATFORM=mac
  ;;

  * )  # Need better than "everything else!
  PLATFORM=windows
  ;;

esac

source "$ROOT/rec/scripts/platform/$PLATFORM.sh"
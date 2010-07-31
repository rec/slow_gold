# Get our name for the current

PLATFORM=other

case "`uname`" in
  "Darwin" )
  PLATFORM=mac
  ;;

  * )
  PLATFORM=windows
  ;;
esac

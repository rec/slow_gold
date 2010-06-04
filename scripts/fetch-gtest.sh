VERSION=1.5.0

wget http://googletest.googlecode.com/files/gtest-$VERSION.tar.bz2
tar xzf gtest-$VERSION.tar.bz2
rm gtest-$VERSION.tar.bz2

ln -s gtest-$VERSION gtest

case "`uname`" in
  "Darwin" )
  OS=mac
  open gtest/xcode/gtest.xcodeproj
  ;;

  * )
  OS=windows
  ;;
esac

echo "Finished installing gtest-$VERSION"

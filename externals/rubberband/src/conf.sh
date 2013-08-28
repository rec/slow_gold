ARGS="--enable-static=yes --enable-shared=no"

./configure\
 $ARGS\
 CXX=clang++\
 CXXFLAGS="-arch i386 -O2 -std=c++11 -stdlib=libc++"\
 --prefix=/development/rec/externals/mac/rubberband\
 && make clean\
 && make install\
 && make clean

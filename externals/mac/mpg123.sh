cd mpg123
./configure\
 --enable-static\
 --enable-shared=no\
 --with-cpu=i386\
 --prefix=/development/rec/externals/mac/mpg123\
 CC=gcc\
 CXXFLAGS="-arch i386"\
 CPPFLAGS="-arch i386"\
 LDFLAGS="-arch i386"\
 && make clean\
 && make\
 && make install

cd ..

#  --enable-shared=no\

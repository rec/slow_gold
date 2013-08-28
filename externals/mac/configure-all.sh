#!/bin/bash

ARGS="--enable-static=yes --enable-shared=no"

cd /development/rec/externals

cd glog

./configure\
 $ARGS\
 CXX=clang++\
 CXXFLAGS="-arch i386 -O2 -std=c++11 -stdlib=libc++"\
 --prefix=/development/rec/externals/mac/glog\
 && make clean\
 && make install\
 && make clean
cd ..

cd mpg123
./configure\
 $ARGS\
 --enable-static\
 --enable-shared=no\
 --with-cpu=i386\
 --prefix=/development/rec/externals/mac/mpg123\
 CC=clang\
 CPPFLAGS="-arch i386 -O2"\
 LDFLAGS="-arch i386"\
 && make clean\
 && make install\
 && make clean
cd ..

cd protobuf
./configure\
 $ARGS\
 CXX=clang++\
 CXXFLAGS="-arch i386 -O2 -std=c++11 -stdlib=libc++"\
 --prefix=/development/rec/externals/mac/protobuf\
 && make clean\
 && make install\
 && make clean
cd ..

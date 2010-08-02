export CC="gcc -arch i136 $EXTRA_CC_FLAGS"

./configure\
 --with-cpu=x86\
 --enable-static\
 --enable-shared=no\
 --prefix=$INSTALL_DIR && \
make && \
make install
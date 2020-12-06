#!/bin/sh -x
echo "compiling for use with GTK-2"
./autogen.sh
./configure --with-gtk=2.0 --enable-gcc-warnings
make


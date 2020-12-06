#!/bin/sh -x
echo "compiling for use with GTK-3"
./autogen.sh
./configure --with-gtk=3.0
#make


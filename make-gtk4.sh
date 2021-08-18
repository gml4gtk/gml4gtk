#!/bin/sh -x
echo "compiling for use with GTK-4"
rm -v -f -r m4
mkdir m4
./autogen.sh
./configure --with-gtk=4
make clean
./dmake



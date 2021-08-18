#!/bin/sh -x
echo "compiling for use with GTK-2"
rm -v -f ./dsmake.*
rm -v -f -r m4
mkdir m4
autoreconf -vfim
./configure --with-gtk=2
make clean
./dmake


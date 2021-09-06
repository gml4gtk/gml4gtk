#!/bin/sh -x
rm -f O1
rm -f O2
rm -f O3
autoreconf -fvim
#./configure CC=clang-11
# fedora has clang version 12
./configure  -with-gtk=4 CC=clang-12
make clean
#scan-build-11 --use-cc=clang-11 make 1>O1 2>O2
# fedora has clang version 12
scan-build --use-cc=clang-12 make 1>O1 2>O2
exit 0
export PATH="/usr/lib/llvm-8/bin:$PATH"
export LD_LIBRARY_PATH="/usr/lib/llvm-8/lib:$LD_LIBRARY_PATH"
alias clang="clang-8"
autoreconf -fvim
make clean
#scan-build -v make
#perl -d -S scan-build make
rm -f O1
rm -f O2
rm -f O3
autoreconf -fvim
./configure CC=clang
make clean
scan-build-8 --use-cc=clang-8 make 1>O1 2>O2
exit 0

perl -d:Trace /usr/bin/scan-build-8 make 1>O1 2>O2

for newer clang dumping json data:
also clang -ast-dump=json test.c
also clang-check -ast-dump -ast-dump-filter=main main.c

also clang -emit-ast main.c

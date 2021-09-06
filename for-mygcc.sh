#!/bin/bash -x
#
# (or use sh -x to see what is going on)
#
# /*
#  *
#  *  This program is free software: you can redistribute it and/or modify
#  *  it under the terms of the GNU General Public License as published by
#  *  the Free Software Foundation, either version 3 of the License, or
#  *  (at your option) any later version.
#  *
#  *  This program is distributed in the hope that it will be useful,
#  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  *  GNU General Public License for more details.
#  *
#  *  You should have received a copy of the GNU General Public License
#  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  *
#  *  These are the four essential freedoms with GNU GPL software:
#  *  1: freedom to run the program, for any purpose
#  *  2: freedom to study how the program works, and change it to make it do what you wish
#  *  3: freedom to redistribute copies to help your Free Software girlfriends and friends
#  *  4: freedom to distribute copies of your modified versions to your Free Software girlfriends and friends
#  *
#  *   ,           ,
#  *  /             \
#  * ((__-^^-,-^^-__))
#  * `-_---'  `---_-'
#  *  `--|o`   'o|--'
#  *      \  `  /
#  *       ): :(
#  *       :o_o:
#  *        "-"
#  *
#  * SPDX-License-Identifier: GPL-3.0+
#  * License-Filename: LICENSE
#  *
#  */
#

# this is c source checking using smatch c checker on sourceforge
# this uses Linux kernel sparse compiler but with many extra checks
#./configure --enable-gcc-warnings CC=$HOME/misc/src/smatch/smatch/cgcc
#make CHECK="~/misc/src/smatch/smatch --full-path" CC=~/misc/src/smatch/smatch/cgcc
#exit 0

# using gcc-10 on debian 11
# using gcc-11.2 on fedora 34
rm -v -f O1 O2 O3
autoreconf -fvim
./configure --with-gtk=3 --enable-gcc-warnings CFLAGS=" -fanalyzer "
make clean
make CC=gcc CFLAGS="-O0 -fanalyzer " 1>O1 2>O2
grep warn O2 >O3
exit 0

# GCC development snapshot in home directory called mygcc
$HOME/mygcc/bin/gcc --version

autoreconf -fvim

# recommended way to do this and CC CFLAGS will not be added to shell environment
# only newest software http://gcc.gnu.org
# gcc-10.1 and gcc-11 has -fanalyzer option
#./configure --enable-gcc-warnings CC=$HOME/mygcc/bin/gcc CFLAGS="-O0 -g -fcallgraph-info "
#./configure --enable-gcc-warnings CC=$HOME/mygcc12/bin/gcc CFLAGS="-g -O0 -fdump-rtl-all-graph -fdump-tree-all-graph -fdump-ipa-all-graph"
#./configure --enable-gcc-warnings CC=$HOME/mygcc12/bin/gcc CFLAGS="-g -O0 -fanalyzer -fdump-analyzer-callgraph -fdump-analyzer-exploded-graph"
./configure --enable-gcc-warnings CC=$HOME/mygcc12/bin/gcc CFLAGS=" -fanalyzer -fcallgraph-info "
#./configure --enable-gcc-warnings CC=$HOME/mygcc/bin/gcc CFLAGS=" -fanalyzer "

make clean
#make
#exit 0

# set to 1/0
doit="0"
if test "$doit" -eq 1; then
CC=$HOME/mygcc/bin/gcc
CFLAGS=" -fanalyzer -Wall -Wextra -fdump-analyzer-callgraph"
$CC $CFLAGS -c -I. -Isrc src/lex.yy.c 1>O1 2>O2
grep warn O2 >O3
exit 0
fi

#make CC=$HOME/mygcc/bin/gcc CFLAGS="-O0 -fcallgraph-info " 1>O1 2>O2
#exit 0

#make CC=$HOME/mygcc12/bin/gcc CFLAGS="-O0 -fanalyzer -fdump-analyzer-callgraph" 1>O1 2>O2
#make CC=$HOME/mygcc12/bin/gcc CFLAGS="-O0 -fanalyzer  -fcallgraph-info" 1>O1 2>O2
make CC=$HOME/mygcc/bin/gcc CFLAGS="-O0 -fanalyzer " 1>O1 2>O2
grep warn O2 >O3

#./configure CC=$HOME/mygcc/bin/gcc

# rtl data gcc/graph.c
#./configure CC=$HOME/mygcc/bin/gcc CFLAGS="-Wall -pedantic -fdump-rtl-all-graph"
#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-rtl-all-graph src/rhp.c

#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-tree-all-graph src/rhp.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-ipa-all-graph src/rhp.c
# this generates vcg file with file extention .ci
#$HOME/mygcc/bin/gcc -c -I. -I.. -fcallgraph-info src/rhp.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info src/dp.c
# da option is dynamic allocation
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info=da src/dp.c
# su is stack usage
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info=su src/dp.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info=su,da src/dpif.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info=su src/vcg.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fcallgraph-info=su,da src/vcgus.c
# these should generate dot files
#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-analyzer-callgraph src/rhp.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-analyzer-exploded-graph src/rhp.c
#$HOME/mygcc/bin/gcc -c -I. -I.. -fdump-analyzer-supergraph src/rhp.c
$HOME/mygcc/bin/gcc --version
exit 0

$HOME/mygcc/bin/gcc -c -I. -I.. -Isrc -fanalyzer -fdump-analyzer-supergraph    src/dpif.c

# -fdump-analyzer-state-purge
# -fdump-analyzer-exploded-graph
# -fdump-analyzer-callgraph
# -fdump-analyzer-supergraph

# -fdump-analyzer-exploded-graph -fdump-analyzer-state-purge -fdump-analyzer-supergraph src/dpif.c
exit 0

# tree data gcc/graph.c
#./configure CC=$HOME/mygcc7/bin/gcc CFLAGS="-Wall -pedantic -fdump-tree-all-graph"

# other gcc dot files do not have options and need gcc debug hacking

#./configure CC=$HOME/mygcc7/bin/gcc CFLAGS="-Wall -pedantic -O2 -fdump-tree-all-graph -fdump-rtl-all-graph"
#./configure CC=$HOME/mygcc/bin/gcc CFLAGS="-Wall -fdump-rtl-expand"

#$HOME/mygcc/bin/gcc --version

# optional support to use clang-3.5 using llvm lib
#./configure CC="clang-3.5 -v"

#clang-3.5 --version

# to check source
#clang --analyze file.c

# optional support to use Linux sparse compiler but does not do c11 standard but can do c99
#./configure CC="sparse"
#sparse --version
# easier: cd src; make CC=sparse

./configure --enable-gcc-warnings CC=$HOME/misc/src/smatch/smatch/cgcc
make CHECK="~/misc/src/smatch/smatch --full-path" CC=~/misc/src/smatch/smatch/cgcc | tee warns.txt

exit 0

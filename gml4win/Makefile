#
# /*
#  *  Copyright 2021
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
#  * SPDX-License-Identifier: GPL-3.0+
#  * License-Filename: LICENSE
#  *
#  */
# makefile to compile gml4win.exe on Linux and test using wine64

gml4win_CC = x86_64-w64-mingw32-gcc

gml4win_WINDRES = x86_64-w64-mingw32-windres

gml4win_SOURCES = \
	gml4win.c \
	../src/gml_parser.c \
	../src/gml_scanner.c \
	../src/bubbling.c \
	../src/sugi2.c \
	../src/sugi3.c \
	../src/sugi4.c \
	../src/sugi5.c \
	../src/pos.c \
	../src/pos2.c \
	../src/pos3.c \
	../src/pos4.c \
	../src/hier.c \
	../src/splay-tree.c \
	../src/uniqstr.c \
	../src/uniqnode.c \
	../src/uniqgraph.c \
	../src/dpif.c \
	../src/dot.tab.c \
	../src/dp.c \
	../src/dpcolor.c \
	../src/dpmisc.c \
	../src/dpun.c \
	../src/dpus.c \
	../src/dpn.c \
	../src/dpe.c \
	../src/dpg.c \
	../src/lex.yy.c \
	../src/rhp.c \
	../src/vcg.flex.c \
	../src/vcg.c \
	../src/vcgus.c \
	../src/vcgun.c


#
gml4win_CFLAGS = \
	-mms-bitfields \
	-I. \
	-I../src \
	-Wall \
	-Wextra

#
gml4win_LIBS = \
	-lgdi32 \
	-lcomctl32 \
	-lcomdlg32

# main entry
all:
	rm -v -f ./gml4win.exe
	./lindent.sh gml4win.c
	$(gml4win_WINDRES) gml4win.rc demo.o
	$(gml4win_CC) -g -c $(gml4win_CFLAGS) $(gml4win_SOURCES)
	$(gml4win_CC) *.o $(gml4win_LIBS) -o gml4win.exe

clean:
	rm -v -f dsmake.*
	rm -v -f *.c~
	rm -v -f gml4win.exe
	rm -v -f *.o

# end

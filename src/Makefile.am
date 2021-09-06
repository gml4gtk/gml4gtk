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
#
# clng llvm control flow graph:
# clang -emit-llvm hello.c -c -o main.bc
# opt -dot-cfg-only main.bc

bin_PROGRAMS=gml4gtk

gml4gtk_SOURCES = \
	gml_parser.c \
	gml_scanner.c \
	main.c \
	bubbling.c \
	sugi2.c \
	sugi3.c \
	sugi4.c \
	sugi5.c \
	pos.c \
	pos2.c \
	pos3.c \
	pos4.c \
	posz.c \
	hier.c \
	splay-tree.c \
	skip-list.c \
	uniqstr.c \
	uniqnode.c \
	uniqgraph.c \
	dpif.c \
	dot.tab.c \
	dp.c \
	dpcolor.c \
	dpmisc.c \
	dpun.c \
	dpus.c \
	dpn.c \
	dpe.c \
	dpg.c \
	lex.yy.c \
	rhp.c \
	vcg.flex.c \
	vcg.c \
	vcgus.c \
	vcgun.c \
	lex.hl.c \
	dphlparser.c \
	dphl.c \
	dpmem.c \
	json.c \
	jgf.c \
	bgv.c \
	bgvparser.c


#
gml4gtk_CFLAGS = \
	@CFLAGS@ @PACKAGE_CFLAGS@ @WARNING_CFLAGS@ @GTK_CFLAGS@

# added zlib
gml4gtk_tolink = @GTK_LIBS@ -lz

# compile with airbus gcc settings
abgcc: $(gml4gtk_SOURCES)
	rm -v -f ./gml4gtk
	rm -v -f ./O1 ./O2
	$(CC) $(AIRBUS_GCC_COMPILER_WARNING) $(GTK_CFLAGS) $(gml4gtk_SOURCES) -I. -I.. $(gml4gtk_tolink) -lm -o gml4gtk 1>O1 2>O2
	$(CC) --version

# compile with airbus gcc settings
abclang: $(gml4gtk_SOURCES)
	rm -f ./gml4gtk
	clang-11 $(AIRBUS_CLANG_COMPILER_WARNING) $(GTK_CFLAGS) $(gml4gtk_SOURCES) -I. -I.. $(gml4gtk_tolink) -lm -o gml4gtk
	clang-11 --version

#
gml4gtk$(EXEEXT): $(gml4gtk_SOURCES)
	rm -f ./gml4gtk
	$(CC) $(gml4gtk_CFLAGS) $(gml4gtk_SOURCES) -I. -I.. $(gml4gtk_tolink) -lm -o gml4gtk
	$(CC) --version

# how to re-generate the parsercode
parsers:
	echo "run and see the mklp.sh shell script"

# make callgraph based on assembly output.
# uses edges.sh script
callgraph:
	make clean
	rm -v -f gml4gtk-callgraph.gv
	rm -v -f gml4gtk-out.gv
	$(CC) -g -S -I. -I.. -O0 $(GTK_CFLAGS) $(gml4gtk_SOURCES)
	echo "digraph callgraph {" >gml4gtk-out.gv
	cat *.s |./mkedges.sh >>gml4gtk-out.gv
	echo "}" >>gml4gtk-out.gv
	echo "/* the gtk library calls:"  >gml4gtk-callgraph.gv
	grep -E '\bgtk_' gml4gtk-out.gv >>gml4gtk-callgraph.gv
	grep -E '\bpango_' gml4gtk-out.gv >>gml4gtk-callgraph.gv
	grep -E '\bg_' gml4gtk-out.gv >>gml4gtk-callgraph.gv
	echo "*/" >>gml4gtk-callgraph.gv
	cat gml4gtk-out.gv  >>gml4gtk-callgraph.gv
	rm -v -f gml4gtk-out.gv

# make callgraph using llvm clang ir bytecode ll file
llvmcallgraph:
	make clean
	clang -c -I. -I.. -S -O0 -emit-llvm  $(GTK_CFLAGS) $(gml4gtk_SOURCES)
	python overcg.py -i splay-tree.ll -o splay-tree.ll.callgraph.gv

# using calltree program
# calls to cairo, pango, gtk are not included this way
# using -x option the external routines are there
# the -x graph is big for gml4gtk
# pkg-config --cflags-only-I gtk+-2.0
# -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/uuid -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/gio-unix-2.0 -I/usr/include/atk-1.0 
cg:
	make clean
	calltree -dot -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/uuid -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/gio-unix-2.0 -I/usr/include/atk-1.0  -I. -I.. $(gml4gtk_SOURCES) >gml4gtk-cg.gv
	calltree -dot -x -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/uuid -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/gio-unix-2.0 -I/usr/include/atk-1.0  -I. -I.. $(gml4gtk_SOURCES) >gml4gtk-externals-cg.gv

# check json jgf
# or:	$(CC) -O0 -g -fdump-ipa-all-graph jsonlint.c json.c -o jsonlint
jsonlint:
	rm -f jsonlint
	$(CC) -O0 -g jsonlint.c json.c -o jsonlint

#
indent:
	./lindent.sh $(gml4gtk_SOURCES) main.h gml_parser.h gml_scanner.h bubbling.h sugi.h pos.h pos2.h pos3.h hier.h splay-tree.h uniqstr.h uniqnode.h uniqgraph.h vcg.h vcgus.h vcg.yy.h vcg.tab.h vcgun.h json.h jgf.h skip-list.h sfg.c sfg.h

# clang -emit-llvm hello.c -c -o main.bc
# opt -dot-cfg-only main.bc
bc:
	clang -emit-llvm -c @CFLAGS@ @PACKAGE_CFLAGS@ @GTK_CFLAGS@ -I. -I.. sugi2.c -o sugi2.bc
	opt-7 -dot-cfg-only sugi2.bc
	opt-7 -dot-cfg sugi2.bc
	opt-7 -dot-dom sugi2.bc
	opt-7 -dot-postdom sugi2.bc
	opt-7 -dot-callgraph sugi2.bc

# windows version
# the G_OS_WIN32 flag is used to change settings in glib-2/gio/ gcredentials.h and uid_t
# the _WIN32 is used by libxml2
gml4gtk_exeCFLAGS = \
	-mms-bitfields \
	-DWIN32 \
	-D_WIN32

# also need zlib.h
gml4gtk_exeincludes = \
	-I../w64/include/gtk-3.0 \
	-I../w64/include/glib-2.0 \
	-I../w64/lib/glib-2.0/include \
	-I../w64/include/pango-1.0 \
	-I../w64/include/cairo \
	-I../w64/include/gdk-pixbuf-2.0 \
	-I../w64/include/atk-1.0 \
	-I../w64/include/

# static link with the dll.a files
gml4gtk_exedlla = \
	../w64/lib/libgobject-2.0.dll.a \
	../w64/lib/libgtk-3.dll.a \
	../w64/lib/libatk-1.0.dll.a \
	../w64/lib/libcairo.dll.a \
	../w64/lib/libcairo-gobject.dll.a \
	../w64/lib/libcairo-script-interpreter.dll.a \
	../w64/lib/libcroco-0.6.dll.a \
	../w64/lib/libffi.dll.a \
	../w64/lib/libfontconfig.dll.a \
	../w64/lib/libfreetype.dll.a \
	../w64/lib/libgailutil-3.dll.a \
	../w64/lib/libgdk-3.dll.a \
	../w64/lib/libgdk_pixbuf-2.0.dll.a \
	../w64/lib/libgio-2.0.dll.a \
	../w64/lib/libglib-2.0.dll.a \
	../w64/lib/libgmodule-2.0.dll.a \
	../w64/lib/libgthread-2.0.dll.a \
	../w64/lib/libjasper.dll.a \
	../w64/lib/libjpeg.dll.a \
	../w64/lib/liblzma.dll.a \
	../w64/lib/libpango-1.0.dll.a \
	../w64/lib/libpangocairo-1.0.dll.a \
	../w64/lib/libpangoft2-1.0.dll.a \
	../w64/lib/libpangowin32-1.0.dll.a \
	../w64/lib/libpixman-1.dll.a \
	../w64/lib/libpng15.dll.a \
	../w64/lib/libpng.dll.a \
	../w64/lib/librsvg-2.dll.a \
	../w64/lib/libtiff.dll.a \
	../w64/lib/libtiffxx.dll.a \
	../w64/lib/libxml2.dll.a \
	../w64/lib/libz.dll.a

gml4gtk_exedlla2 = \
	-llibgobject-2.0.dll.a \
	-llibgtk-3.dll.a \
	-llibatk-1.0.dll.a \
	-llibcairo.dll.a \
	-llibcairo-gobject.dll.a \
	-llibcairo-script-interpreter.dll.a \
	-llibcroco-0.6.dll.a \
	-llibffi.dll.a \
	-llibfontconfig.dll.a \
	-llibfreetype.dll.a \
	-llibgailutil-3.dll.a \
	-llibgdk-3.dll.a \
	-llibgdk_pixbuf-2.0.dll.a \
	-llibgio-2.0.dll.a \
	-llibglib-2.0.dll.a \
	-llibgmodule-2.0.dll.a \
	-llibgthread-2.0.dll.a \
	-llibjasper.dll.a \
	-llibjpeg.dll.a \
	-lliblzma.dll.a \
	-llibpango-1.0.dll.a \
	-llibpangocairo-1.0.dll.a \
	-llibpangoft2-1.0.dll.a \
	-llibpangowin32-1.0.dll.a \
	-llibpixman-1.dll.a \
	-llibpng15.dll.a \
	-llibpng.dll.a \
	-llibrsvg-2.dll.a \
	-llibtiff.dll.a \
	-llibtiffxx.dll.a \
	-llibxml2.dll.a \
	-llibz.dll.a


# cross compiling windows 64bit exe on linux
# static linking should be theoretically possible
# but any usable docs are missing
gml4gtkexe: main.c
	x86_64-w64-mingw32-windres gml4gtk.rc demo-gml4gtk.o
	x86_64-w64-mingw32-gcc -c $(gml4gtk_exeCFLAGS)  -I. -I.. $(gml4gtk_exeincludes) $(gml4gtk_SOURCES)
	x86_64-w64-mingw32-gcc -v *.o -Wl,-Bstatic $(gml4gtk_exedlla) -Wl,-Bdynamic -o gml4gtk.exe
# this does not worl
#	x86_64-w64-mingw32-gcc -v -L. *.o -Wl,-Bstatic -l $(gml4gtk_exedlla) -Wl,-Bdynamic -o gml4gtk.exe
# this does not work
#	x86_64-w64-mingw32-gcc *.o -L../w64/lib/ $(gml4gtk_exedlla2) -o gml4gtk64.exe
# 32 bits compiling does not work on debian or fedora
#	x86_64-w64-mingw32-windres --target=pe-i386 gml4gtk.rc demo-gml4gtk.o
#	i686-w64-mingw32-gcc -m32 -c $(gml4gtk_exeCFLAGS)  -I. -I.. $(gml4gtk_exeincludes) $(gml4gtk_SOURCES)
#	cp 0gtk.bin 0gtk.a
#	i686-w64-mingw32-gcc -v -Wl,-bpe-i386 -m32 *.o 0gtk.a -o 0big.o
#	result: the gtk binary compiled code cannot be used because it is compiled with gcc compiler older then version 10

# this generate a 32bit windos exe which still needs dll's
# but installed the fedora mingw static gtk-2
# this does not work yet
pe:
	i686-w64-mingw32-windres gml4gtk.rc demo-gml4gtk.o
	i686-w64-mingw32-gcc -I. -I.. $(gml4gtk_SOURCES) `i686-w64-mingw32-pkg-config --cflags gtk+-win32-2.0` `i686-w64-mingw32-pkg-config --libs gtk+-win32-2.0` -lz -o 0o.exe

#
clean-generic:
	rm -v -f *.bc
	rm -v -f ./massif.out.*
	rm -v -f ./*.rhp.txt
	rm -v -f ./a.out
	rm -v -f *~
	rm -v -f ./*.so.1
	rm -v -f ./*.o
	rm -v -f ./*.a
	rm -v -f ./*.i
	rm -v -f ./*.s
	rm -v -f ./O
	rm -v -f ./OO
	rm -v -f ./O1
	rm -v -f ./O2
	rm -v -f ./O3
	rm -v -f ./ID
	rm -v -f ./dsmake.output
	rm -v -f ./dsmake.warnings
	rm -v -f ./dsmake.errors
	rm -v -f *.dot
	rm -v -f *.ll
	rm -v -f *.*r.*
	rm -v -f *.*t.*
	rm -v -f *.bc
	rm -v -f *.plist
	rm -v -f *.ps
	rm -v -f ./*.exe
	rm -v -f jsonlint
	rm -v -f ./*.gk*
	rm -v -f ./*.out
	rm -v -f ./*.res
	rm -v -f ./gml4gtk-cg.gv
	rm -v -f *.scallgraph.gv
	rm -v -f -r .deps
	rm -v -f *graph-info.gv
	rm -v -f *graph-info.svg
	rm -v -f *graph-info.ci
	rm -v -f *.ci
	rm -v -f gml4gtk-*


# /* end */

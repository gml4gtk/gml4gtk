#
# /*
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
	pos.c \
	pos2.c \
	pos3.c \
	hier.c \
	splay-tree.c \
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
	vcgun.c


#
gml4gtk_CFLAGS = \
	@CFLAGS@ @PACKAGE_CFLAGS@ @WARNING_CFLAGS@ @GTK_CFLAGS@

#
gml4gtk_tolink = @GTK_LIBS@

#
gml4gtk$(EXEEXT): $(gml4gtk_SOURCES)
	$(CC) $(gml4gtk_CFLAGS) $(gml4gtk_SOURCES) -I. -I.. $(gml4gtk_tolink) -lm -o gml4gtk

#
indent:
	./Lindent $(gml4gtk_SOURCES) main.h gml_parser.h gml_scanner.h bubbling.h sugi.h pos.h pos2.h pos3.h hier.h splay-tree.h uniqstr.h uniqnode.h uniqgraph.h vcg.h vcgus.h vcg.yy.h vcg.tab.h vcgun.h

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

gml4gtk_exeincludes = \
	-I../w64/include/gtk-3.0 \
	-I../w64/include/glib-2.0 \
	-I../w64/lib/glib-2.0/include \
	-I../w64/include/pango-1.0 \
	-I../w64/include/cairo \
	-I../w64/include/gdk-pixbuf-2.0 \
	-I../w64/include/atk-1.0


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


# cross compiling windows 64bit exe on linux
gml4gtkexe: main.c
	x86_64-w64-mingw32-windres gml4gtk.rc demo-gml4gtk.o
	x86_64-w64-mingw32-gcc -c $(gml4gtk_exeCFLAGS)  -I. -I.. $(gml4gtk_exeincludes) $(gml4gtk_SOURCES)
	x86_64-w64-mingw32-gcc *.o -Wl,-Bstatic $(gml4gtk_exedlla) -o gml4gtk.exe

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
	rm -v -f *.*r.*
	rm -v -f *.*t.*
	rm -v -f *.bc
	rm -v -f *.plist
	rm -v -f *.ps
	rm -v -f ./*.exe

# /* end */

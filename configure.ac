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
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# Macro: AC_INIT (package, version, [bug-report], [tarname], [url])
# minor version number is increased at important feature change
# Process with autogen.sh or manual:
# aclocal
# autoheader
# autoconf
# libtoolize --force --automake
# automake -a --gnu --include-deps
# or do this all using autoreconf
#
# test also using scan-build from llvm clang tools
#

AC_PREREQ([2.69])
AC_INIT([gml4gtk], [7.2], [mooigraph@gmail.com], [gml4gtk.tar.gz], [https://sourceforge.net/projects/gml4gtk])
AC_CONFIG_SRCDIR([src/main.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

AC_COPYRIGHT([
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
])

AC_LANG(C)

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# -DFORTIFY_SOURCE=2 does add glibc extra checks, see RedHat documentation
# Need c11 mode because of %llu in printf() and (long long int) datatype and unnamed unions
# Upcoming c standard is c17 using GNU GCC -std=c17
# or CFLAGS="$CFLAGS ..."
# do not optimize away memset()
#CFLAGS="$CFLAGS -g -std=c99 -fno-builtin-memset -DFORTIFY_SOURCE=2 -fdump-rtl-expand-graph"
# -pg for use with gprof
# -fcallgraph-info should generate graph data
# using -fno-inline when testing with valgrind
#CFLAGS="$CFLAGS -g -std=c99 -fno-builtin-memset -DFORTIFY_SOURCE=2"
#CFLAGS="$CFLAGS -g -std=c99 -O0"
# asm output: -S -fverbose-asm
# asm output: -Wa,-adhln=test-O3.s -g -fverbose-asm -masm=intel
# asm output: -fverbose-asm -save-temps=obj
CFLAGS="$CFLAGS -g -std=c99 "

# Gcc compiler options
# the option -frecord-gcc-switches puts the compiler options
# in the binary ro read with: readelf -p .GCC.command.line a.out
# https://github.com/Barro/compiler-warnings has lists of gcc options
AC_DEFUN([GCC_COMPILER_WARNING],
[AC_MSG_CHECKING(whether compiler accepts $1)
AC_SUBST(WARNING_CFLAGS)
ac_save_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $1"
AC_TRY_COMPILE(,
[int x;],
WARNING_CFLAGS="$WARNING_CFLAGS $1"
AC_MSG_RESULT(yes),
AC_MSG_RESULT(no))
CFLAGS="$ac_save_CFLAGS"])

# the fortify -D option needs optimizing, cannot use -O0 then.
# for debug with gdb the -O0 is needed or it cannot find crashes.
# prints gcc settings and include files and is very verbose
# when extra warnings are enabled then -DMEMCHECK is set
# extra code in dpmem.c starts checking for memory leaks.
# GCC_COMPILER_WARNING(--verbose)
# GCC_COMPILER_WARNING(-H)
AC_ARG_ENABLE(gcc-warnings,
              AC_HELP_STRING([--enable-gcc-warnings],
	                     [turn on lots of GCC warnings (not recommended)]),
[case "${enableval}" in
   yes|no) ;;
   *)      AC_MSG_ERROR([unknown value ${enableval} for gcc-warnings option expected yes or no]) ;;
 esac],
              [enableval=no])
if test "${enableval}" = yes; then
  GCC_COMPILER_WARNING(-Werror)
  AC_SUBST([WERROR_CFLAGS], [$WARNING_CFLAGS])
  WARNING_CFLAGS=
  GCC_COMPILER_WARNING(-O0)
  GCC_COMPILER_WARNING(-Wall)
  GCC_COMPILER_WARNING(-Wextra)
  GCC_COMPILER_WARNING(-W)
  GCC_COMPILER_WARNING(-Wbad-function-cast)
  GCC_COMPILER_WARNING(-Wcast-align)
  GCC_COMPILER_WARNING(-ftrapv)
  GCC_COMPILER_WARNING(-fno-inlne)
  GCC_COMPILER_WARNING(-Wformat)
  GCC_COMPILER_WARNING(-Wmissing-declarations)
  GCC_COMPILER_WARNING(-Wmissing-prototypes)
  GCC_COMPILER_WARNING(-Wnested-externs)
  GCC_COMPILER_WARNING(-Wshadow)
  GCC_COMPILER_WARNING(-Wstrict-prototypes)
  GCC_COMPILER_WARNING(-Woverlength-strings)
  GCC_COMPILER_WARNING(-Wformat-nonliteral)
  GCC_COMPILER_WARNING(-Wformat-security)
  GCC_COMPILER_WARNING(-Winit-self)
  GCC_COMPILER_WARNING(-Winline)
  GCC_COMPILER_WARNING(-Wmisleading-indentation)
  GCC_COMPILER_WARNING(-Wlogical-op)
  GCC_COMPILER_WARNING(-Wduplicated-cond)
  GCC_COMPILER_WARNING(-Wtautological-compare)
  GCC_COMPILER_WARNING(-Wshift-count-negative)
  GCC_COMPILER_WARNING(-Wshift-count-overflow)
  GCC_COMPILER_WARNING(-Wshift-negative-value)
  GCC_COMPILER_WARNING(-Wshift-overflow)
  GCC_COMPILER_WARNING(-Wnull-dereference)
  GCC_COMPILER_WARNING(-Wnonnull)
  GCC_COMPILER_WARNING(-Woverride-init-side-effects)
  GCC_COMPILER_WARNING(-Wunused-const-variable)
  GCC_COMPILER_WARNING(-Wframe-address)
  GCC_COMPILER_WARNING(-ftrack-macro-expansion=1)
  GCC_COMPILER_WARNING(-DMEMCHECK)
else
  WARNING_CFLAGS=
  GCC_COMPILER_WARNING(-Wall)
  GCC_COMPILER_WARNING(-Wshadow)
  GCC_COMPILER_WARNING(-Wno-overlength-strings)
  GCC_COMPILER_WARNING(-pedantic)
  GCC_COMPILER_WARNING(-D_FORTIFY_SOURCE=2)
  GCC_COMPILER_WARNING(-fstack-protector-strong)
  GCC_COMPILER_WARNING(-Wl,-O1)
  GCC_COMPILER_WARNING(-frecord-gcc-switches)
  GCC_COMPILER_WARNING(-Wpointer-arith)
  GCC_COMPILER_WARNING(-fvar-tracking-assignments)
  GCC_COMPILER_WARNING(-fcompare-debug)
  GCC_COMPILER_WARNING(-flto)
  GCC_COMPILER_WARNING(-fwhole-program)
fi

#  GCC compiler rtl and tree data generation
#  GCC_COMPILER_WARNING(-fdump-lang-all-graph)
#  GCC_COMPILER_WARNING(-fdump-rtl-all-graph)
#  GCC_COMPILER_WARNING(-fdump-tree-all-graph)
#  GCC_COMPILER_WARNING(-fdump-ipa-all-graph)
#  GCC_COMPILER_WARNING(-fcallgraph-info)

#? AC_INCLUDE_DEFAULTS([stdio.h math.h])

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h stdint.h string.h inttypes.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset strdup])

AC_CHECK_SIZEOF([void *])
AC_CHECK_SIZEOF([uintptr_t])

#-------------------------------------------
# Check for math.h include and math library.
# Old distros, use CHECK as a SEARCH backup.
AC_CHECK_HEADER([math.h],
  AC_SEARCH_LIBS([cos],[m],[have_libm=yes],
    AC_CHECK_LIB([m],[cos],[have_libm=yes])))
if test x"${have_libm}" != xyes; then
   AC_MSG_FAILURE([gml4gtk-configure.ac-ERROR: Please install Math libraries and math.h include files for libm],[1])
fi

#-------------------------------------------
# Check for C99 hypot. Error if none found.
# Older compilers will have to set/use C99.
AC_CHECK_FUNCS(hypot, ,[AC_MSG_FAILURE([ERROR: hypot() required but not found.],[1])])

#-------------------------------------------
# Check for C99 isfinite or finite. Use one.
math_isfinite=no
math_finite=no
AC_CHECK_FUNCS(isfinite,
  [AC_DEFINE(HAVE_ISFINITE, 1)
   math_isfinite=true],
  [AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
      [[#include <math.h>]],
      [[double f = 0.0; isfinite(f)]])],
    [AC_DEFINE(HAVE_ISFINITE, 1)
     math_isfinite=true],
      [AC_CHECK_FUNCS(finite,
        [AC_DEFINE(HAVE_FINITE, 1)
         math_finite=true])])])

if test x"${math_isfinite}" = xno && test x"${math_finite}" = xno; then
  AC_MSG_FAILURE([ERROR: isfinite() or finite() required but not found.],[1])
fi

AC_SUBST(HAVE_FINITE)
AC_SUBST(HAVE_ISFINITE)


# default to gtk+-2.0 setting to 1
GTK_HAVE_API_VERSION_2=0
GTK_HAVE_API_VERSION_3=1
GTK_HAVE_API_VERSION_4=0

AC_ARG_ENABLE(gtk2,
[  --enable-gtk2           Use GTK 2.0 in preference to GTK 3.0 [[default=no]]],
[if test "$enableval" = "yes"
then
  prefer_gtk2=yes
else
  prefer_gtk2=no
fi])

AC_MSG_CHECKING([which gtk+ version to compile against])
AC_ARG_WITH([gtk],
  [AS_HELP_STRING([--with-gtk=2.0|3.0|4.0],[which gtk+ version to compile against (default: 3.0)])],
  [case "$with_gtk" in
     2.0|3.0|4.0) ;;
     *) AC_MSG_ERROR([invalid gtk version specified]) ;;
   esac],
  [with_gtk=2.0])
AC_MSG_RESULT([$with_gtk])

case "$with_gtk" in
  2.0) GTK_API_VERSION=2.0
       GTK_REQUIRED=2.0.0
       GTK_HAVE_API_VERSION_2=1
       GTK_HAVE_API_VERSION_3=0
       GTK_HAVE_API_VERSION_4=0
       ;;
  3.0) GTK_API_VERSION=3.0
       GTK_REQUIRED=2.91.0
       GTK_HAVE_API_VERSION_2=0
       GTK_HAVE_API_VERSION_3=1
       GTK_HAVE_API_VERSION_4=0
       ;;
  4.0) GTK_API_VERSION=4.0
       GTK_REQUIRED=3.91.0
       GTK_HAVE_API_VERSION_2=0
       GTK_HAVE_API_VERSION_3=0
       GTK_HAVE_API_VERSION_4=1
       ;;
esac

#
AC_SUBST([GTK_API_VERSION])
AC_SUBST([GTK_REQUIRED])


#
AM_CONDITIONAL([HAVE_GTK_2],[test "$with_gtk" = "2.0"])
AM_CONDITIONAL([HAVE_GTK_3],[test "$with_gtk" = "3.0"])
AM_CONDITIONAL([HAVE_GTK_4],[test "$with_gtk" = "4.0"])

#
AC_DEFINE_UNQUOTED([GTK_HAVE_API_VERSION_2], [$GTK_HAVE_API_VERSION_2], [gtk version 2])
AC_DEFINE_UNQUOTED([GTK_HAVE_API_VERSION_3], [$GTK_HAVE_API_VERSION_3], [gtk version 3])
AC_DEFINE_UNQUOTED([GTK_HAVE_API_VERSION_4], [$GTK_HAVE_API_VERSION_4], [gtk version 4])

# Preliminary check for pkg-config
if test -z "$PKG_CONFIG"; then
   AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
fi
if test "$PKG_CONFIG" = "no" ; then
   echo "
Please install pkg-config and then reconfigure mooigraph.
pkg-config is available from http://www.freedesktop.org/
"
   exit 1
fi

# glib 2.0 (needed even if not building GUI; we need 2.14 for regexp functions)
PKG_CHECK_MODULES(GLIB, glib-2.0 >= 2.14.0, have_glib2="yes", have_glib2="no")
if test "${have_glib2}" = "no" ; then
   echo "
Please install glib-2.0 >= 2.14.0 and then reconfigure mooigraph.
glib-2.0 is available from http://www.gtk.org/
"
   exit 1
fi

# Initial check for GTK availability
if test "$prefer_gtk2" = "yes" ; then
    PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= 2.14.0,
      GTK_CFLAGS=$GTK2_CFLAGS
      GTK_LIBS=$GTK2_LIBS
      CFLAGS="$CFLAGS $GTK_CFLAGS"
      LIBS="$LIBS $GTK_LIBS"
      gtk_version="2.0",
      echo "GTK 2 >= 2.14.0 not found"
    )
elif test "$prefer_gtk2" = "no" ; then
    PKG_CHECK_MODULES(GTK3, gtk+-3.0 >= 3.0.1,
      GTK_CFLAGS=$GTK3_CFLAGS
      GTK_LIBS=$GTK3_LIBS
      CFLAGS="$CFLAGS $GTK_CFLAGS"
      LIBS="$LIBS $GTK_LIBS"
      dnl AC_DEFINE(USE_GTK3)
      gtk_version="3.0"
      fake_gtkspinner="no",
      echo "GTK 3 >= 3.0.1 not found"
    )
fi

dnl GTK 2.0 fallback in case preference not given
if test "$prefer_gtk2" = "no" && test "$gtk_version" = "none" ; then
      PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= 2.14.0,
        GTK_CFLAGS=$GTK2_CFLAGS
        GTK_LIBS=$GTK2_LIBS
        CFLAGS="$CFLAGS $GTK_CFLAGS"
        LIBS="$LIBS $GTK_LIBS"
        gtk_version="2.0",
        build_gui="no"
        echo "GTK 2 >= 2.14.0 not found"
    )
fi

dnl Detect Win32 compiler
AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    platform_win32=yes
    HAVE_PLATFORM_WIN32=1
    ;;
  *)
    platform_win32=no
    HAVE_PLATFORM_WIN32=0
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")
AC_SUBST([PLATFORM_WIN32])
AC_DEFINE_UNQUOTED([PLATFORM_WIN32], [$HAVE_PLATFORM_WIN32], [using a windows compiler])

# compilation date in config.h
CONFIG_DATE=`date +"%a %x %Y"`

AC_SUBST(CONFIG_DATE)

AC_DEFINE_UNQUOTED(COMPILE_DATE, ["$CONFIG_DATE"], [Year, month and day this program is compiled.])

# short system name in config.h
CONFIG_UNAME=`uname -s`

AC_SUBST(CONFIG_UNAME)

AC_DEFINE_UNQUOTED(COMPILE_UNAME, ["$CONFIG_UNAME"], [System where this is compiled.])

#
PKG_CHECK_MODULES(GTK, gtk+-$GTK_API_VERSION >= $GTK_REQUIRED)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

# final compiler settings
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(WARNING_CFLAGS)

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

echo "                     "
echo "                     "
echo "                     "
echo "   ,           ,     "
echo "  /             \    "
echo " ((__-^^-,-^^-__))   "
echo " '-__- -   '--__-    "
echo "    -O       O-      "
echo "      \     /        "
echo "       ): :(         "
echo "       :o_o:         "
echo "         -           "
echo "                     "
echo "                     "
echo "                     "

echo This system is `uname -a`;

cat <<EOF

$PACKAGE_NAME $VERSION is ready to be built.

The following settings will be used:

Use "make" to compile $PACKAGE_NAME $VERSION.

use ./configure --with-gtk=2.0 for gtk-2
use ./configure --with-gtk=3.0 for gtk-3
use ./configure --with-gtk=4.0 for gtk-4
use ./configure --enable-gcc-warnings to enable gcc warnings and checks

EOF

AC_MSG_NOTICE([

Configuration:
  Source code location	${srcdir}
  Build code location	${builddir}
  Destination prefix	${prefix}
  C-Compiler		${CC}
  Config GTK version	"${with_gtk}"
  Config warning flags	"${WARNING_CFLAGS}"
  Config CFLAGS		"${CFLAGS}"
  Config LIBS		"${LIBS}"
  Config GTK_CFLAGS	"${GTK_CFLAGS}"
  Config GTK_LIBS	"${GTK_LIBS}"
  Config PACKAGE_CFLAGS	"$PACKAGE_CFLAGS"
  Config PLATFORM_WIN32	"$platform_win32"
  Config COMPILE_DATE	"$CONFIG_DATE"
  Config COMPILE_UNAME	"$CONFIG_UNAME"
])

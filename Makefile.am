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

#
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

#
AM_MAKEFLAGS = --no-print-directory

#
AUTOMAKE_OPTIONS = foreign subdir-objects

# dirs with makefile.am
SUBDIRS = . src

#
NULL =

#
EXTRA_DIST = \
	$(NULL)

#
MAINTAINERCLEANFILES = \
	Makefile \
	Makefile.in \
	aclocal.m4 \
	configure \
	config.sub \
	config.guess \
	config.status \
	compile \
	depcomp \
	install-sh \
	ltmain.sh \
	missing \
	config.h.in \
	dmake.output \
	dsmake.output \
	dsmake.errors \
	dsmake.warnings \
	autoscan.log \
	configure.scan \
	config.h.in~ \
	config.log \
	stamp-h1 \
	src/Makefile.in \
	src/Makefile \
	src/*.i \
	src/*.s \
	autom4te.cache/* \
	m4/*.m4 \
	ylwrap \
	ID \
	$(NULL)

#
cleaner: ## make cleaner then make distclean
	make clean
	make maintainer-clean-generic
	rm -vfr autom4te.cache
	rm -vf src/Makefile.in
	rm -vfr src/.deps
	rm -vfr src/.libs
	rm -vf ./libtool
	rm -vfr ./m4
	rm -vf ./*~
	rm -vf ./O1
	rm -vf ./O2
	rm -vf ./O3
	rm -vf ./*.ci
	rm -vf ./*.o
	rm -vf ./*.dot
	rm -vf ./*.gml
	rm -vf a-conftest*


# generate git statistics
# %d\t%d number is lines added/deleted in a file
gitlog: ## generate git statistics
	git log --numstat >gitlog.txt

# use as sudo debain check install to create R=rpm, S=slackware or D=debian package
# first run autogen.sh and make for a binary
checkinstall: ## create rpm, deb or tgz package using the checkinstall program
	checkinstall -D --install=no

.PHONY: help

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

# end

#!/bin/sh -x

#flex dot.l
flex -Sflex.skl dot.l
#flex dphl.l
flex -Sflex.skl dphl.l

echo "generating vcg lexer"
# -d   == add debug code
# -8   == generate 8 bits scanner
# -f   == fast large scanner
# -R   == reentrant lexer for threaded parsing
flex -Sflex.skl -d -8 -f --yylineno --prefix=vcg --outfile=vcg.flex.c vcg.l


rm dot.tab.c
rm dot.tab.h
rm dot.output
rm dot.xml
echo "generating dot lexer and parser"

bison -d --graph=dot.gv -x dot.y
cat dot.xml |xsltproc xml2dot.xsl - >dot2.gv
cat dot.xml |xsltproc xml2text.xsl - >dot2.txt
cat dot.xml |xsltproc xml2gml.xsl - >dot2.gml
cat dot.xml |xsltproc xml2xhtml.xsl - >dot2.html

echo "generating dot html lexer and parser"
bison -d --graph=dphl.gv dphl.y
#
echo "flex 2.6.4 lexers generate warnings using scan-build and gcc-11"
flex --version
bison --version
#
diff -p flex.skl flex-2.6.4.skl >flex-skl-diff.txt

echo "debian has flex 2.6.4"
echo "fedora has flex version 2.6.4"

echo "debian has bison version 3.3.2"
echo "fedora has bison version 3.7.4"

#  Using own customized skeleton for the lexer code:
#   flex -S myflex.skl -o mylexer.c mylexer.l
#  Generate the myflex.skl from the development repo with:
#   sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=5 -DFLEX_SUBMINOR_VERSION=33 | sed 's/m4postproc_/m4_/g' > myflex.skl
#  Then edit the myflex.skl and test with needed fixes
# sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex-2.4.6.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=4 -DFLEX_SUBMINOR_VERSION=6 | sed 's/m4postproc_/m4_/g' > myflex.skl


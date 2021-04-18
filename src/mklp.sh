#!/bin/sh -x
rm dot.tab.c
rm dot.tab.h
rm dot.output
rm dot.xml
rm lex.yy.c
echo "generating dot lexer and parser"

#flex dot.l
flex -Sflex.skl dot.l
bison -d --graph=dot.gv -x dot.y
echo "generating dot html lexer and parser"
#flex dphl.l
flex -Sflex.skl dphl.l
bison -d --graph=dphl.gv dphl.y
echo "generating vcg lexer"
# -d   == add debug code
# -8   == generate 8 bits scanner
# -f   == fast large scanner
# -R   == reentrant lexer for threaded parsing
#flex -d -8 -f --yylineno --prefix=vcg --outfile=vcg.flex.c vcg.l
flex -Sflex.skl -d -8 -f --yylineno --prefix=vcg --outfile=vcg.flex.c vcg.l
#
echo "flex 2.6.4 lexers generate warnings using scan-build and gcc-11"
flex --version
bison --version
#
diff -p flex.skl flex-2.6.4.skl >flex-skl-diff.txt

#  Using own customized skeleton for the lexer code:
#   flex -S myflex.skl -o mylexer.c mylexer.l
#  Generate the myflex.skl from the development repo with:
#   sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=5 -DFLEX_SUBMINOR_VERSION=33 | sed 's/m4postproc_/m4_/g' > myflex.skl
#  Then edit the myflex.skl and test with needed fixes
# sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex-2.4.6.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=4 -DFLEX_SUBMINOR_VERSION=6 | sed 's/m4postproc_/m4_/g' > myflex.skl

# using gcc-11 -fanalyzer says some buffers may leak memory in flex lexer
# but that is not true, it does not detec the use of yylex_destroy()

#!/bin/sh -x

#flex dot.l
flex -Sflex.skl dot.l
#flex dphl.l
flex -Sflex.skl dphl.l

echo "generating lexers"
# -d   == add debug code
# -8   == generate 8 bits scanner
# -f   == fast large scanner
# -R   == reentrant lexer for threaded parsing
# --tables-file=vcg.tables.c generates binary table data
flex  -Sflex.skl -d -8 -f --yylineno --prefix=vcg --outfile=vcg.flex.c vcg.l

echo "flex 2.6.4 on debian 11 works"
echo "flex 2.6.4 on fedora 34 crashes"

# special skeleton to write only the dfa table data
# after manual edit it is usable for own yylex() routine
# flex  -Sflextables.skl -d -8 -f --yylineno --prefix=vcg --outfile=vcg.flextables.c vcg.l


flex --version
bison --version
#
diff -p flex.skl flex-2.6.4.skl >flex-skl-diff.txt

echo "debian 11 has flex 2.6.4"
echo "debian 10 has flex 2.6.4"
echo "fedora 34 has flex version 2.6.4"


#  Using own customized skeleton for the lexer code:
#   flex -S myflex.skl -o mylexer.c mylexer.l
#  Generate the myflex.skl from the development repo with:
#   sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=5 -DFLEX_SUBMINOR_VERSION=33 | sed 's/m4postproc_/m4_/g' > myflex.skl
#  Then edit the myflex.skl and test with needed fixes
# sed 's/m4_/m4postproc_/g; s/m4preproc_/m4_/g' flex-2.4.6.skl | m4 -P -DFLEX_MAJOR_VERSION=2 -DFLEX_MINOR_VERSION=4 -DFLEX_SUBMINOR_VERSION=6 | sed 's/m4postproc_/m4_/g' > myflex.skl


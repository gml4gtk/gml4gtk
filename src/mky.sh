#!/bin/sh -x



rm dot.tab.c
rm dot.tab.h
rm dot.output
rm dot.xml
echo "generating parser"

bison -d --graph=dot.gv -x dot.y
cat dot.xml |xsltproc xml2dot.xsl - >dot2.gv
cat dot.xml |xsltproc xml2text.xsl - >dot2.txt
cat dot.xml |xsltproc xml2gml.xsl - >dot2.gml
cat dot.xml |xsltproc xml2xhtml.xsl - >dot2.html

echo "generating dot html parser"
bison -d --graph=dphl.gv dphl.y

echo "debian 10 has bison version 3.3.2"
echo "debian 10 has bison version 3.7.5"
echo "fedora 34 has bison version 3.7.4"



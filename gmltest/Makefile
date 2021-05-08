
CFLAGS = -g -Wall -Wextra $(OFLAGS) $(XFLAGS)
OFLAGS = -DDEBUG
PACKCC=./packcc


all : gml

# option --debug to packcc

gml: gml.peg
	$(PACKCC) --debug  gml.peg
	$(CC) $(CFLAGS) gml.c -o gml
	cat t.gml |./gml

clean :
	rm -f *~ *.o
	rm -v -f gml
	rm -v -f gml.c
	rm -v -f gml.h


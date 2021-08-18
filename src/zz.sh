#!/bin/sh -x
rm ./O1
rm ./O2
rm ./O3
valgrind -v --tool=memcheck --leak-check=full --suppressions=valgrind-suppressions --suppressions=gtk.supp --suppressions=gtk64.supp --suppressions=glib.supp ./gml4gtk 1>O1 2>O2
# the -A options shows the next 3 lines
# in the backtrace where the calloc came from
grep dp_calloc -A 3 O2 >O3
grep dp_free -A 3 O2 >>O3
# use after free
grep use -A 3 O2 >>O3
grep Invalid -A 3 O2 >>O3

# run valgrind to check for memory leaks
# -v -v options add more verbose output
# --show-reachable=yes show reachable memory, but also shows it in the linked thread lib code
# --tool=memcheck use the memcheck tool, there are other tools too
# --leak-check=full show all info
# --show-reachable=yes show reachable memory
# --track-fds=yes show open file descriptors
# --trace-children=yes trace forked children
# --log-file=00valgrindlog.txt write to log file
# gml4gtk uses monly calloc() and free() to check in the log file


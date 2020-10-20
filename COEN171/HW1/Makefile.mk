CC      = gcc
PC      = fpc
PROGS   = psort csort ctree ptree stack

all:            $(PROGS)

clean:;         rm -f $(PROGS) *.o

psort:          sort.p
                $(PC) -opsort sort.p

csort:          sort.c
                $(CC) -o csort sort.c

ptree:          tree.p
                $(PC) -optree tree.p

ctree:          tree.c
                $(CC) -o ctree tree.c

stack:          stack.p
                $(PC) -ostack stack.p

queens:         queens.c
                $(CC) -o queens queens.c
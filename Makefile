CC=gcc
CFLAGS = -g -Wall

CSRC = $(wildcard src/datastructures/*.c) \
	   $(wildcard src/commons/*.c) \
	   $(wildcard src/*.c)

COBJ = $(CSRC:.c=.o)
CDEP = $(COBJ:.o=.d)

tester: $(COBJ)
	$(CC) -o $@ $^

-include $(CDEP)

$.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@ -lm

.PHONY: clean
clean:
	rm -f $(COBJ) tester

.PHONY: cleandep
cleandep:
	rm -f $(CDEP)

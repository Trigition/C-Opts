CC=g++
CFLAGS = -g -Wall 
CSRC = $(wildcard src/compilers/*.cpp) \
	   $(wildcard src/parsers/*cpp) \
	   $(wildcard src/commons/*.cpp) \
	   $(wildcard src/*.cpp)

COBJ = $(CSRC:.cpp=.o)
CDEP = $(COBJ:.o=.d)

tester: $(COBJ)
	$(CC) -o $@ $^ 

-include $(CDEP)

$.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(COBJ) tester

.PHONY: cleandep
cleandep:
	rm -f $(CDEP)

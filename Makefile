CC=g++ -std=c++17
CFLAGS = -g -Wall
CSRC = $(wildcard src/compilers/*.cpp) \
	   $(wildcard src/parsers/*cpp) \
	   $(wildcard src/commons/*.cpp) \
	   $(wildcard src/*.cpp)

COBJ = $(CSRC:.cpp=.o)
CDEP = $(COBJ:.o=.d)

TESTSRC = $(wildcard test/*.cpp)
TESTOBJ = $(TESTSRC:.cpp=.o) $(COBJ)
TESTDEP = $(TESTOBJ:.o=.d)

all: copt runtest

copt: $(COBJ)
	$(CC) -o $@ $^ 

runtest: $(TESTOBJ)
	$(CC) -o $@ $^

-include $(CDEP)
-include $(TESTDEP)

$.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(COBJ) copt
	rm -f $(TESTOBJ) runtest

.PHONY: cleandep
cleandep:
	rm -f $(CDEP)
	rm -f $(TESTDEP)

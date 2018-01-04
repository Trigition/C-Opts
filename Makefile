CC=g++
CFLAGS = -g -Wall
LDFLAGS = -L ../boost_1_66_0/
CSRC = $(wildcard src/datastructures/*.cpp) \
	   $(wildcard src/commons/*.cpp) \
	   $(wildcard src/*.cpp)

COBJ = $(CSRC:.cpp=.o)
CDEP = $(COBJ:.o=.d)

tester: $(COBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(CDEP)

$.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(COBJ) tester

.PHONY: cleandep
cleandep:
	rm -f $(CDEP)

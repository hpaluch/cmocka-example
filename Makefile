
CFLAGS  = -Wall -g
LDFLAGS = -g
LDLIBS_CMOCKA = -lcmocka
LDFLAGS_CMOCKA = -Wl,--wrap=write -Wl,--wrap=read

all : example test

example : example.o io_tools.o

example.o  : example.c io_tools.h
io_tools.o : io_tools.c

test : test.o io_tools.o
	$(LINK.o) $(LDFLAGS_CMOCKA) $^ $(LOADLIBES) $(LDLIBS_CMOCKA) -o $@
test.o : test.c

.PHONY: run
run : example
	./example

.PHONY: test_mocka
test_mocka : test
	./test

.PHONY: clean
clean:
	rm -f example test *.o


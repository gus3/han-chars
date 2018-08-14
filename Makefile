LINKER = 
CCOPTS = $(LINKER)
CC = gcc $(CCOPTS)
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -O0 -fcond-mismatch
OBJECTS = lookup.o unihan.o lookup-test.o utf8-conv.o utf8-conv-test.o
INCFLAGS = 
LDFLAGS = $(DEBUG)
LIBS = 

all: test unihan-translate

test: lookup-test utf8-conv-test

unihan-translate: lookup.o utf8-conv.o main.o unihan.o unicode-names.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

main.o: main.c
	$(CC) -c -o $@ $^ $(LDFLAGS) $(LIBS)

lookup-test: lookup.o lookup-test.o unihan.o unicode-names.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

utf8-conv-test: utf8-conv.o utf8-conv-test.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

clean:
	rm -f *.o

.PHONY: all
.PHONY: clean

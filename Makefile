CC=g++
CFLAGS=-Wall -Wextra -Werror
SOURCES=main.cpp sources/onegin.cpp sources/my_qsort.cpp
HEADERS=sources/onegin.h sources/my_qsort.h
EXECUTABLE=onegin

all: build_main

build_main:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

debug:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) -D DEBUG

rebuild: clean all

clean:
	rm $(EXECUTABLE)
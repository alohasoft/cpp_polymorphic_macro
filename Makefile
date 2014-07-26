CPP=clang++

CPPFLAGS=-std=c++11

.PHONY: all test clean

test: binary
	./binary

all: binary

binary: runtime_static_typing.cc
	${CPP} ${CPPFLAGS} -o $@ $<

clean:
	rm -rf binary

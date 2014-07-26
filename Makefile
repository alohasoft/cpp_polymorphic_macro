CPP=clang++

CPPFLAGS=-std=c++11

.PHONY: all test clean

test: binary
	./binary

all: binary

binary: polymorphic_macro.cc
	${CPP} ${CPPFLAGS} -o $@ $<

clean:
	rm -rf binary

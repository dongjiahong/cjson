
vapth = src/json/:include/

BIN = bin/main

CXX ?= g++
CFLAG = --std=c++11

JSON_OBJECT = src/json/*.cpp

.PHONY: all test clean

all:
	${CXX} ${CFLAG} -o ${BIN} ${JSON_OBJECT}

test:
	rm -f ${BIN}


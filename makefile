CC=g++
CFLAGS=-c -Wall
SOURCES = $(wildcard *.cpp)
EXECS = $(SOURCES:%.cpp=%)

all: $(EXECS)
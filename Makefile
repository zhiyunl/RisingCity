# IDIR =../include
# # IDIR = ./
# CXX=g++
# CXXFLAGS=-I$(IDIR) -Wall -g
#
# ODIR=obj
# LDIR =../lib
# # LDIR = ./
#
# LIBS=-lm
#
# _DEPS = MinHeap.h MyQueue.h FileParser.h RBTree.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#
# _OBJ = main.o MinHeap.o MyQueue.o FileParser.o RBTree.o
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#
#
# $(ODIR)/%.o: %.c $(DEPS)
# 	$(CXX) -c -o $@ $< $(CXXFLAGS)
#
# main: $(OBJ)
# 	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
#
# .PHONY: clean
#
# clean:
# 	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

PROGRAM = risingCity
CXX = g++
CXXFLAGS = -std=c++0x

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(wildcard *.h)

default: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${PROGRAM}

clean:
	rm -f ${OBJECTS} ${PROGRAM}
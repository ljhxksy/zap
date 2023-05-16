###
### Makefile for zap project
###
### zap is a program specifically used for compressing and decompressing text 
### files using the Huffman coding algorithm.
###
### Author:  Anh Hoang ahoang05
###

MAKEFLAGS += -L

CXX      = clang++ 
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

##
##  --- Delete these comments and put appropriate comments in ---
##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##
## CAUTION:  DO NOT JUST USE THE OLD RULES FOR 'clean'!!!
##   
##
##  --- Delete these comments and put appropriate comments in ---


zap: main.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o BinaryIO.o 
	${CXX} ${LDFLAGS} -o zap $^

main.o: main.cpp HuffmanCoder.o
	$(CXX) $(CXXFLAGS) -c main.cpp

# phaseOne.o: phaseOne.h phaseOne.cpp
#  	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

HuffmanCoder.o: HuffmanCoder.h HuffmanCoder.cpp
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

## Rules for compiling unit test
unit_test: unit_test_driver.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o \
		   BinaryIO.o
	$(CXX) $(CXXFLAGS) $^

provide:
	provide comp15 proj3_zap README Makefile unit_tests.h \
					main.cpp HuffmanCoder.h HuffmanCoder.cpp \
					test_text.txt test1.txt test2.txt test3.txt

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
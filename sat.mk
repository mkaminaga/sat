# makefile
# date 2017-09-13
# Copyright 2017 Mamoru kaminaga
TARGET = libsat.a
SRC = sat.cc util.cc
OBJDIR = build
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cc=.o)))

GCC = g++
INCLUDE = -I ~/projects/mkaminaga/ -I ~/projects/library/
CFLAGS = -std=c++0x -g -Wall -O2 -DUNICODE
LIBS = -lrt -lstdc++

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

$(OBJDIR)/%.o: %.cc
	mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

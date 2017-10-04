# makefile
# date 2017-09-13
# Copyright 2017 Mamoru kaminaga
TARGET = test.out
SRC = sat.cc test.cc util.cc
OBJDIR = build
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cc=.o)))

GCC = g++
INCLUDE = -I ~/projects/mkaminaga/ -I ~/projects/library/
CFLAGS = -std=c++0x -g -Wall -O2 -DUNICODE
LIBS = -lrt -lstdc++ ~/projects/library/tle/v2.1.0/libtle.a
LDFLAGS =

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: %.cc
	mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) $(INCLUDE) -o $@ -c $^

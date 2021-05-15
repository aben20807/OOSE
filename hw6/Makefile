CXX := g++-8
CXXFLAGS := -std=c++1z -Wall -Wextra -O2
DBGFLAGS := -g3 -ggdb -O0
# CXXFLAGS = $(DBGFLAGS)

SRCDIR := .
ROOTDIR = $(realpath .)
# BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGETS := main

all: $(TARGETS)

mk_dirs:
	@mkdir -p $(BINDIR)

$(TARGETS): %: mk_dirs $(BINDIR)/%;

$(BINDIR)/%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

format:
	$(eval FILES := $(shell find $(SRCDIR)/ -type f -name '*.cc' -or -name '*.h'))
	clang-format-10 -style=file -i $(FILES)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -rf $(BINDIR)/*"; $(RM) -rf $(BINDIR)/*

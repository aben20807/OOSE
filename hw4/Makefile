CXX := g++-8
CXXFLAGS := -std=c++1z -Wall -Wextra -O2
DBGFLAGS := -g3 -ggdb
# CXXFLAGS = $(DBGFLAGS)


SRCDIR := src
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGET := bus_booking_system

.PHONY: all clean mk_dirs booking_framework bus_booking_system movie_booking_system format
all: $(TARGET)

mk_dirs:
	@mkdir -p $(BUILDDIR) $(BINDIR)

bus_booking_system: mk_dirs
	@$(MAKE) -C $(SRCDIR)/$@ --no-print-directory ROOTDIR=$(ROOTDIR) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"

movie_booking_system: mk_dirs
	@$(MAKE) -C $(SRCDIR)/$@ --no-print-directory ROOTDIR=$(ROOTDIR) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"

format:
	$(eval FILES := $(shell find $(SRCDIR)/ -type f -name '*.cc' -or -name '*.h'))
	clang-format -style=file -i $(FILES)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -rf $(BUILDDIR) $(BINDIR)/*"; $(RM) -rf $(BUILDDIR) $(BINDIR)/*

CXX := g++-8
CXXFLAGS := -std=c++1z -Wall -Wextra

SRCDIR := src
FRAMEWORKDIR := booking_framework
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGET := booking_bus

.PHONY: all clean mk_build_dir booking_framework booking_bus
all: $(TARGET)

mk_dirs:
	@mkdir -p $(BUILDDIR) $(BINDIR)

booking_framework: mk_dirs
	@$(MAKE) -C $(SRCDIR)/$@  --no-print-directory ROOTDIR=$(ROOTDIR) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"

booking_bus: booking_framework
	@$(MAKE) -C $(SRCDIR)/$@  --no-print-directory ROOTDIR=$(ROOTDIR) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"

booking_movie: booking_framework
	@$(MAKE) -C $(SRCDIR)/$@  --no-print-directory ROOTDIR=$(ROOTDIR) CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)"

clean:
	@echo " Cleaning...";
	@echo " $(RM) -rf $(BUILDDIR)"; $(RM) -rf $(BUILDDIR)

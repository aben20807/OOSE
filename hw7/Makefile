CXX := g++-8
CXXFLAGS := -std=c++1z -Wall -Wextra -O2 -pthread
LDFLAGS := -Wall -Wextra -O2 -pthread
DBGFLAGS := -g3 -ggdb -O0
# CXXFLAGS = $(DBGFLAGS)

SRCDIR := .
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGET := $(BINDIR)/main

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR)/ -type f -name '*.$(SRCEXT)')
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))

all: $(TARGET)

mk_dirs:
	mkdir -p $(BINDIR) $(BUILDDIR)

# $(TARGETS): %: mk_dirs $(BINDIR)/%;
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $(LDFLAGS) $^ -o $@"; $(CXX) $(LDFLAGS) $^ -o $@

# $(BINDIR)/%: %.cc
# 	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " $(CXX) $(CXXFLAGS) -c -o $@ $<"; $(CXX) $(CXXFLAGS) -c -o $@ $<

format:
	$(eval FILES := $(shell find $(SRCDIR)/ -type f -name '*.cc' -or -name '*.h'))
	clang-format-10 -style=file -i $(FILES)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -rf $(BINDIR)/* $(BUILDDIR)/*"; $(RM) -rf $(BINDIR)/* $(BUILDDIR)/*

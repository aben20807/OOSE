SRCDIR := .
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGET := $(BINDIR)/booking_movie

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR)/ -type f -name '*.$(SRCEXT)')
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))
LIB := -static -L$(BUILDDIR) -lbooking_framework

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LIB)"; $(CXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " $(CXX) $(CXXFLAGS) -c -o $@ $<"; $(CXX) $(CXXFLAGS) -c -o $@ $<
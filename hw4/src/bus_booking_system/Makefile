SRCDIR := .
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin
TARGET := $(BINDIR)/booking_bus

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR)/ -type f -name '*.$(SRCEXT)')
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))

all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET)"; $(CXX) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " $(CXX) $(CXXFLAGS) -c -o $@ $<"; $(CXX) $(CXXFLAGS) -c -o $@ $<
SRCDIR := .
ROOTDIR = $(realpath .)
BUILDDIR := $(ROOTDIR)/build
TARGET := $(BUILDDIR)/libbooking_framework.a

SRCEXT := cc
SOURCES := $(shell find $(SRCDIR)/ -type f -name '*.$(SRCEXT)')
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))

all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	@echo " ar rcs $(TARGET) $(OBJECTS)"; ar rcs $(TARGET) $(OBJECTS)
	@$(RM) $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " $(CXX) $(CXXFLAGS) -c -o $@ $<"; $(CXX) $(CXXFLAGS) -c -o $@ $<
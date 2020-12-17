#Compiler/Linker
CXX         := c++

#Target binary
TARGET      := runner

# default python version
PYTHON_BIN     ?= python3
PYTHON_CONFIG  := $(PYTHON_BIN)-config
PYTHON_INCLUDE ?= $(shell $(PYTHON_CONFIG) --includes)
EXTRA_FLAGS    := $(PYTHON_INCLUDE)

#Directories
SRCDIR      := ./src
INCDIR      := ./include
BUILDDIR    := ./build
TARGETDIR   := ./bin
RESDIR      := ./resources
IDEASDIR    := ./ideas
TESTDIR     := ./test
DOCDIR      := ./doc
DOCUMENTSDIR:= ./documents

SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CXXFLAGS    +=  -std=c++17 -Wno-conversion -g3 #-std=c++17 -O3 -Wall -pedantic -Wno-vla-extension -I/usr/local/include/ -I/usr/local/include/eigen3/ -I./include -I./src
LFLAGS      := -std=c++17 -O3 -Wall -Wno-deprecated -Werror -pedantic -L/usr/local/lib/
LIB         := -framework OpenGL -framework GLUT
INC         := -I$(INCDIR) -I/usr/local/include -I/usr/include/opengl -I./include -DNDEBUG
INCDEP      := -I$(INCDIR)

PY_LDFLAGS  += $(shell if $(PYTHON_CONFIG) --ldflags --embed >/dev/null; then $(PYTHON_CONFIG) --ldflags --embed; else $(PYTHON_CONFIG) --ldflags; fi)

EXTRA_FLAGS += $(shell $(PYTHON_BIN) $(CURDIR)/numpy_flags.py)
WITHOUT_NUMPY := $(findstring $(EXTRA_FLAGS), WITHOUT_NUMPY) 

#Source and Object files
SOURCES     := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Documentation (Doxygen)
DOXY        := /usr/local/Cellar/doxygen/1.8.20/bin/doxygen
DOXYFILE    := $(DOCDIR)/Doxyfile

#default make (all)
all: resources tester ideas $(TARGET)

#make regarding source files
sources: resources $(TARGET)

#remake
remake: cleaner all

#copy Resources from Resources Directory to Target Directory
resources: directories
	@cp -r $(RESDIR)/ $(TARGETDIR)/

#make directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#clean objects
clean:
	@$(RM) -rf $(BUILDDIR)

#clean objects and binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT)) #$(INCDIR)/matplotlibcpp.h

#link
$(TARGET): $(OBJECTS) #$(INCDIR)/matplotlibcpp.h
	$(CXX) $(LFLAGS) $(PY_LDFLAGS) $(INC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) #$(INCDIR)/matplotlibcpp.h
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(EXTRA_FLAGS) $(INC) -c -o $@ $< $(PY_LDFLAGS)
	@$(CXX) $(CXXFLAGS) $(EXTRA_FLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp


#compile test files
tester: directories
ifneq ("$(wildcard $(TESTDIR)/*.$(SRCEXT) )","")
	$(CXX) $(CXXFLAGS) test/*.cpp $(INC) $(LIB) -o bin/tester
else
	@echo "No $(SRCEXT)-files within $(TESTDIR)!"
endif


#compile idea files
ideas: directories
ifneq ("$(wildcard $(IDEASDIR)/*.$(SRCEXT) )","")
	$(CXX) $(CXXFLAGS) ideas/*.cpp $(INC) $(LIB) -o bin/ideas
else
	@echo "No $(SRCEXT)-files within $(IDEASDIR)!"
endif

doxyfile.inc: #Makefile
	@echo INPUT            = README.md . $(SRCDIR)/ $(INCDIR)/ $(DOCUMENTSDIR)/ > $(DOCDIR)/doxyfile.inc
	@echo FILE_PATTERNS     = "*.md" "*.h" "*.$(SRCEXT)" >> $(DOCDIR)/doxyfile.inc
	@echo OUTPUT_DIRECTORY = $(DOCDIR)/ >> $(DOCDIR)/doxyfile.inc

doc: doxyfile.inc
	$(DOXY) $(DOXYFILE) &> $(DOCDIR)/doxygen.log
	@$(MAKE) -C $(DOCDIR)/latex/ &> $(DOCDIR)/latex/latex.log
	@mkdir -p "./docs"
	cp -r "./doc/html/" "./docs/"

#Non-File Targets
.PHONY: all remake clean cleaner resources sources directories ideas tester doc

#
# CS11 C++ Advanced Ray Tracer
#
# Eduardo Gonzalez
#


### Variable setup for all programs

CC	= gcc
CXX	= g++
MAKEDEPEND	= $(CXX) -M
CFLAGS  	= -Wall -g
CXXFLAGS	= -Wall -g

# add flags for gtest
CXXFLAGS        += -I gtest
LDFLAGS_TEST     = -lgtest -lpthread $(LDFLAGS)

# ISO C++11 standard (or working version fallback for older compilers)
# (XXX Need an automated test for this)
CXXFLAGS        += -std=c++0x
#CXXFLAGS       += -std=c++11


### Source file lists for each program

# Src files for vector_test
VECTEST_CXXSRCS = vector_test.cc
VECTEST_OBJS    = $(VECTEST_CXXSRCS:.cc=.o)

COLORTEST_CXXSRCS = color_test.cc color.cc
COLORTEST_OBJS    = $(COLORTEST_CXXSRCS:.cc=.o)


### Dependencies and generic build rules

# Dependency files
DEPS	 = $(patsubst %.cc,deps/%.d,$(VECTEST_CXXSRCS))
DEPS	+= $(patsubst %.cc,deps/%.d,$(COLORTEST_CXXSRCS))


# Programs to build in make 'all', 'test', or 'all-full'
PROGS	= 
PROGS_TEST = color_test vector_test
PROGS_FULL = $(PROGS) $(PROGS_TEST)


# Default build rule
# (Main programs)
all: $(PROGS)

# Test utilities
test: $(PROGS_TEST)

# Complete build
# (also includes test utilities)
all-full: $(PROGS_FULL)

clean:
	rm -f *.o deps/*.d $(PROGS_FULL)
	rmdir deps


### Build rules for programs

vector_test: $(VECTEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS_TEST)

color_test: $(COLORTEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS_TEST)


### Build rule templates

# Generate dependency files
deps/%.d : %.cc
	mkdir -p deps
	$(MAKEDEPEND) -o $@ $<

include $(DEPS)

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

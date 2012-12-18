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
CXXFLAGS       += -I gtest
LDFLAGS_TEST    = -lgtest -lpthread $(LDFLAGS)

# add flags for boost
BOOST_INC       = boost
CXXFLAGS       += -I $(BOOST_INC)

# ISO C++11 standard (or working version fallback for older compilers)
# (XXX Need an automated test for this)
CXXFLAGS        += -std=c++0x
#CXXFLAGS       += -std=c++11


### Source file lists for each program

# Src files for the raytracer
RAYTRACER_CXXSRCS  = rt.cc
RAYTRACER_CXXSRCS += ray.cc color.cc
RAYTRACER_CXXSRCS += sceneobject.cc sphere.cc plane.cc cylinder.cc
RAYTRACER_CXXSRCS += scene.cc camera.cc light.cc
RAYTRACER_OBJS     = $(RAYTRACER_CXXSRCS:.cc=.o);

# Src files for vector_test
VECTEST_CXXSRCS = vector_test.cc
VECTEST_OBJS    = $(VECTEST_CXXSRCS:.cc=.o)

# Src files for color_test
COLORTEST_CXXSRCS = color_test.cc color.cc
COLORTEST_OBJS    = $(COLORTEST_CXXSRCS:.cc=.o)

# Src files for intersect_test
INTXNTEST_CXXSRCS  = intersect_test.cc ray.cc color.cc sceneobject.cc
INTXNTEST_CXXSRCS += sphere.cc plane.cc
INTXNTEST_OBJS     = $(INTXNTEST_CXXSRCS:.cc=.o)


### Dependencies and generic build rules

# Dependency files
DEPS	 = $(patsubst %.cc,deps/%.d,$(VECTEST_CXXSRCS))
DEPS	+= $(patsubst %.cc,deps/%.d,$(COLORTEST_CXXSRCS))
DEPS	+= $(patsubst %.cc,deps/%.d,$(INTXNTEST_CXXSRCS))
DEPS	+= $(patsubst %.cc,deps/%.d,$(RAYTRACER_CXXSRCS))


# Programs to build in make 'all', 'test', or 'all-full'
PROGS	= rt
PROGS_TEST = color_test vector_test intersect_test
PROGS_FULL = $(PROGS) $(PROGS_TEST)

# Declare phony build rules
.PHONY : all test all-full docs clean

# Default build rule
# (Main programs)
all: $(PROGS)

# Test utilities
test: $(PROGS_TEST)

# Complete build
# (also includes test utilities)
all-full: $(PROGS_FULL)

docs:
	doxygen

clean:
	rm -f deps/*.d *.o $(PROGS_FULL)
	rm -rf docs/*
	rmdir deps
	rmdir docs


### Build rules for programs

rt: $(RAYTRACER_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

vector_test: $(VECTEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS_TEST)

color_test: $(COLORTEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS_TEST)

intersect_test: $(INTXNTEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS_TEST)

### Build rule templates

# Generate dependency files
deps/%.d : %.cc
	mkdir -p deps
	$(MAKEDEPEND) $(CXXFLAGS) -o $@ $<

include $(DEPS)

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

EXAMPLE_CPP := $(wildcard example/*.cpp)
EXAMPLE_OUT := $(EXAMPLE_CPP:example/%.cpp=%.bin)

CXXFLAGS := -Wall -std=c++11 -I.
CXX := clang++
LDFLAGS := -lGLEW -lglfw3 -lXi -lXrandr

ifeq ($(RELEASE),1)
  CXXFLAGS += -O3
else
	CXXFLAGS += -g
endif

ifeq ($(ASAN), 1)
	CXXFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif


.PHONY: clean all clear new fancy test

all: $(EXAMPLE_OUT)

%.bin: example/%.cpp lumina/lumina.a
	$(CXX) $(CXXFLAGS) -o $@ $< lumina/lumina.a $(LDFLAGS)


clean:
	rm -f *.bin
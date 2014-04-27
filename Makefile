GAME_CPP := $(wildcard example/*.cpp)
GAME_OBJ := $(GAME_CPP:%.cpp=obj/%.o)

CXXFLAGS := -Wall -std=c++1y -I.
CXX := clang++
LDFLAGS := -lGLEW -lglfw3 -lXi -lXrandr

ifeq ($(DEBUG), 1)
  CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

ifeq ($(ASAN), 1)
	CXXFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif


.PHONY: makelumina clean all clear new fancy

all: makelumina test

test: $(GAME_OBJ) lumina/lumina.a
	$(CXX) -o $@ $(GAME_OBJ) lumina/lumina.a $(LDFLAGS)

makelumina: 
	cd lumina && $(MAKE) DEBUG=$(DEBUG) ASAN=$(ASAN) CXX=$(CXX)

lumina/lumina.a: makelumina

obj/%.o: %.cpp $(ALL_HPP) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir obj obj/example

clean:
	rm -rf obj
	rm -f test

cleanall: clean
	cd lumina && $(MAKE) clean

clear:
	clear

fancy: clear all

new: clear clean all
newall: clear cleanall all
################################################################################
# generate file lists
################################################################################
CONFIG_HPP 	:= $(wildcard config/*.hpp)

CORE_HPP 		:= $(wildcard core/*.hpp)
CORE_CPP		:= $(wildcard core/*.cpp)
CORE_OBJ		:= $(CORE_CPP:%.cpp=obj/%.o)

SERVICE_HPP := $(wildcard service/*.hpp)
SERVICE_CPP := $(wildcard service/*.cpp)
SERVICE_OBJ	:= $(SERVICE_CPP:%.cpp=obj/%.o)

VIDEO_HPP  	:= $(wildcard video/*.hpp) $(wildcard video/gl/*.hpp)
VIDEO_CPP 	:= $(wildcard video/*.cpp) $(wildcard video/gl/*.cpp)
VIDEO_OBJ		:= $(VIDEO_CPP:%.cpp=obj/%.o)

# join lists
ALL_OBJ 		:= $(CORE_OBJ) $(SERVICE_OBJ) $(VIDEO_OBJ)
ALL_HPP			:= $(CONFIG_HPP) $(CORE_HPP) $(SERVICE_HPP) $(VIDEO_HPP)


################################################################################
# configurate compiler
################################################################################
CXXFLAGS := -g -Wall -std=c++11
CXX := clang++
ARFLAGS := -r

ifeq ($(DEBUG), 1)
  CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

ifeq ($(ASAN), 1)
	CXXFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

################################################################################
# define targets and dependencies
################################################################################
.PHONY: clean fancy clear

lumina.a: $(ALL_OBJ)
	$(AR) $(ARFLAGS) $@ $(ALL_OBJ)

obj/%.o: %.cpp $(ALL_HPP) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj: 
	mkdir obj obj/core obj/service obj/util obj/video obj/video/gl

clean:
	rm -rf obj
	rm -f lumina.a

fancy: clear lumina.a 

clear:
	clear
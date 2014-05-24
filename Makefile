################################################################################
#generate file lists
################################################################################
CONFIG_HPP 	:= $(wildcard config/*.hpp)

INPUT_HPP 	:= $(wildcard input/*.hpp)

UTIL_HPP 		:= $(wildcard util/*.hpp)

CORE_HPP 		:= $(wildcard core/*.hpp)
CORE_CPP		:= $(wildcard core/*.cpp)
CORE_OBJ		:= $(CORE_CPP:%.cpp=obj/%.o)

SERVICE_HPP := $(wildcard service/*.hpp)
SERVICE_CPP := $(wildcard service/*.cpp)
SERVICE_OBJ	:= $(SERVICE_CPP:%.cpp=obj/%.o)

VIDEO_HPP  	:= $(wildcard video/*.hpp) $(wildcard video/gl/*.hpp)
VIDEO_CPP 	:= $(wildcard video/*.cpp) $(wildcard video/gl/*.cpp)
VIDEO_OBJ		:= $(VIDEO_CPP:%.cpp=obj/%.o)

SCENE_HPP 	:= $(wildcard scene/*.hpp)
SCENE_CPP		:= $(wildcard scene/*.cpp)
SCENE_OBJ		:= $(SCENE_CPP:%.cpp=obj/%.o)

# join lists
ALL_OBJ 		:= $(CORE_OBJ) $(SERVICE_OBJ) $(VIDEO_OBJ) $(SCENE_OBJ)
ALL_HPP			:= $(CONFIG_HPP) $(INPUT_HPP) $(CORE_HPP) $(SERVICE_HPP) 
ALL_HPP 		+= $(VIDEO_HPP) $(UTIL_HPP) $(SCENE_HPP)


################################################################################
# configurate compiler
################################################################################
CXXFLAGS := -Wall -std=c++11
CXX := clang++
ARFLAGS := -r

ifeq ($(RELEASE),1)
  CXXFLAGS += -O3
else
	CXXFLAGS += -g
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
	mkdir obj obj/core obj/service obj/util obj/video obj/video/gl obj/scene

clean:
	rm -rf obj
	rm -f lumina.a
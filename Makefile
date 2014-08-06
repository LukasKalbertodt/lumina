################################################################################
#generate file lists
################################################################################
CONFIG_HPP  := $(wildcard config/*.hpp) $(wildcard config/*.tpp)

INPUT_HPP   := $(wildcard input/*.hpp) $(wildcard input/*.tpp)

UTIL_HPP    := $(wildcard util/*.hpp) $(wildcard util/*.tpp)

CORE_HPP    := $(wildcard core/*.hpp) $(wildcard core/*.tpp)
CORE_CPP    := $(wildcard core/*.cpp)
CORE_OBJ    := $(CORE_CPP:%.cpp=obj/%.o)

SERVICE_HPP := $(wildcard service/*.hpp) $(wildcard service/*.tpp)
SERVICE_CPP := $(wildcard service/*.cpp)
SERVICE_OBJ := $(SERVICE_CPP:%.cpp=obj/%.o)

VIDEO_HPP   := $(wildcard video/*.hpp) $(wildcard video/*.tpp)
VIDEO_CPP   := $(wildcard video/*.cpp)
VIDEO_OBJ   := $(VIDEO_CPP:%.cpp=obj/%.o)

SCENE_HPP   := $(wildcard scene/*.hpp) $(wildcard scene/*.tpp)
SCENE_CPP   := $(wildcard scene/*.cpp)
SCENE_OBJ   := $(SCENE_CPP:%.cpp=obj/%.o)

IO_HPP      := $(wildcard io/*.hpp) $(wildcard io/*.tpp)
IO_CPP      := $(wildcard io/*.cpp)
IO_OBJ      := $(IO_CPP:%.cpp=obj/%.o)

# join lists
ALL_OBJ     := $(CORE_OBJ) $(SERVICE_OBJ) $(VIDEO_OBJ) $(SCENE_OBJ) $(IO_OBJ)
ALL_HPP     := $(CONFIG_HPP) $(INPUT_HPP) $(CORE_HPP) $(SERVICE_HPP) 
ALL_HPP     += $(VIDEO_HPP) $(UTIL_HPP) $(SCENE_HPP) $(IO_HPP)


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
	mkdir obj obj/core obj/service obj/util obj/video obj/video/gl obj/scene obj/io

clean:
	rm -rf obj
	rm -f lumina.a
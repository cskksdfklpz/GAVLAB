CXX      := -g++
CXXFLAGS := -std=c++14 -stdlib=libc++ -Wno-deprecated 
LDFLAGS  := -framework GLUT -framework OpenGL
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
DAT_DIR  := ./data
OUT_DIR  := ./output
TARGET   := gavlab
INCLUDE  := -Iinclude/ 
SRC      := $(wildcard src/*.cpp)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ 

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS) 


.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG_TEST\(fmt,arg...\)=printf\(\"[debug]:\ \"\ fmt,\#\#arg\) -g
debug: all

release: CXXFLAGS += -O3 -DDEBUG_TEST\(fmt,arg...\)=\{\}
release: all

run: 
	clear
	# launch the simulation system
	build/apps/$(TARGET)

clean:
	clear
	# cleaning the binary files and data files
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	

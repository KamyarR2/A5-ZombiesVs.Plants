CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXE = game.out
SRC_DIR := ./src
HEAD_DIR := ./include
MEDIA_DIR = ./Media
OBJ_DIR := ./obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HEAD_FILES = $(wildcard $(HEAD_DIR)/*.hpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(HEAD_DIR)

$(EXE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LFLAGS) -o $@

.PHONY: all clean

all: $(EXE)

clean:
	rm -f $(OBJ_FILES) $(EXE)

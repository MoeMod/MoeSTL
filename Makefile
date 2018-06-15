CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17

BIN		:= bin
SRC		:= .
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= MoeSTL


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
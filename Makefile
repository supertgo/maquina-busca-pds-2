CXX := g++
CXX_FLAGS := 

SRC := src
BIN := build
INCLUDE := include
LIB := entidades
LIBRARIES :=
MAIN := main
EXECUTABLE := tp_execution

OBJECTS := $(patsubst $(SRC)/$(LIB)/%.cpp,$(BIN)/%.o,$(wildcard $(SRC)/$(LIB)/*.cpp))
MAIN_OBJECT := $(BIN)/$(MAIN).o


##O executavel vpl_execution
all: $(EXECUTABLE)

# Rodando o executavel 
run: all
	clear
	./$(EXECUTABLE)

# Linkando o executavel com os objetos no build
$(EXECUTABLE): $(OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

$(BIN)/%.o: $(SRC)/$(LIB)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c $< -o $@

$(MAIN_OBJECT): $(SRC)/$(MAIN).cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	-rm -r build
	-rm $(EXECUTABLE)
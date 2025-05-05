# Build settings
CXX := g++
SRC_DIR := code
OBJ_DIR := obj

ALL_SRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES := $(filter-out $(SRC_DIR)/test.cpp, $(ALL_SRC))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS := -std=c++17 -fdiagnostics-color=always -g
LDFLAGS :=  # Add any libraries if needed
TARGET := Game.out

# Build rules
$(TARGET): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ_DIR)/*.o

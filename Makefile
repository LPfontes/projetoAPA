CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Define os diretórios
BUILD_DIR = ./build
SRC_DIR = ./src
INCLUDE_DIR = ./include

# Lista todos os arquivos de origem .cpp no diretório src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/*/*.cpp)

# Cria a lista de arquivos objeto (.o) com base nos .cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Define o nome do executável final
TARGET = $(BUILD_DIR)/prog

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra de compilação para cada arquivo .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D) # Cria o diretório de build se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET) < entrada.txt

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)/* $(TARGET)

.PHONY: debug
debug:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/debug_prog $(SRCS) -I$(INCLUDE_DIR)
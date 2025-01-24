# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++17

# Diretórios
SRC_DIR = codigos
INC_DIR = headers
DB_DIR = database
MAIN_DIR = .

# Arquivo main
MAIN_SRC = main.cpp

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(DB_DIR)/database.cpp $(MAIN_SRC)

# Objetos correspondentes
OBJS = $(SRCS:.cpp=.o)

# Nome do executável
TARGET = $(MAIN_DIR)/programa

# Regra padrão
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ $^

# Compilação dos objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(DB_DIR)/%.o: $(DB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	del /Q $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

# Nom de l'exécutable
TARGET = GameOfLife

# Répertoire des fichiers d'en-têtes
INCLUDE_DIR = include

# Répertoires des fichiers sources
SRC_DIR = src

# Liste des fichiers sources
SRC_FILES = $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/Cell.cpp \
            $(SRC_DIR)/Grid.cpp \
            $(SRC_DIR)/GameOfLife.cpp \
            $(SRC_DIR)/Button.cpp

# Options de compilation
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Règle par défaut
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)

# Règle pour reconstruire
rebuild: clean all

.PHONY: all clean rebuild

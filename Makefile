# Compilateur
CC = gcc

# Dossiers
SRC_DIR = src
INCLUDE_DIR = include
ASSETS_DIR = assets
BIN_DIR = bin

# Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

# Options de compilation
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Options de débogage
DEBUG_FLAGS = -g

# Nom de l'exécutable
EXECUTABLE = $(BIN_DIR)/introGame

# Variable pour activer/désactiver le mode débogage
DEBUG = 0

# Si DEBUG est activé, on ajoute les flags de débogage
ifeq ($(DEBUG), 1)
    CFLAGS += $(DEBUG_FLAGS)
endif

# Règle par défaut
all: $(EXECUTABLE)

# Compilation de l'exécutable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

# Compilation des fichiers objets
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(BIN_DIR)  # Crée le répertoire bin s'il n'existe pas
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(BIN_DIR)/*

# Exécution du programme
exe:
	./$(EXECUTABLE)

# Cible pour compiler en mode débogage
debug:
	$(MAKE) DEBUG=1

.PHONY: all clean exe debug
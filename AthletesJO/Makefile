# Nom du compilateur
CC = gcc

# Options du compilateur
#CFLAGS = -Wall -Wextra -O2
CFLAGS = -w -Wextra -O2


# Nom du fichier source
SRC = athletesJO.c common.c history.c manageAthletesData.c statistics.c

# Nom de l'exécutable généré
TARGET = AthletesJO.exe

# Bibliothèques à lier
LIBS = -lstdc++

# Règle par défaut
all: $(TARGET)

# Règle pour générer l'exécutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Règle pour nettoyer les fichiers générés
clean:
	del $(TARGET)

.PHONY: all clean
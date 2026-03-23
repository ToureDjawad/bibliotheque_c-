
# Le compilateur
CXX = g++

# Les options de compilation (-Wall pour les erreurs, -Wextra pour les avertissements supplémentaires, -std=c++17 pour le standard C++17)
CXXFLAGS = -Wall -Wextra -std=c++17

# Nom de l'exécutable final
EXEC = 	app

# Liste des fichiers objets 
OBJ = main.o fonctions.o

# Commande de nettoyage (rm -f pour Linux/Mac, del pour Windows)
RM = rm -f

# Règle par défaut (lance l'édition de liens)
all : $(EXEC)

# Édition de liens : lie les .o pour créer l'exécutable
$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ)

# Compilation des fichiers sources (.cpp) en fichiers objets (.o)
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Nettoyage des fichiers objets et de l'exécutable
clean :
	$(RM) $(EXEC) *.o
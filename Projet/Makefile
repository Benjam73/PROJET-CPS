# Makefile du projet PLS RICM3 2016-2017
# @author : BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Enzo


# Choix du compilateur
CC=gcc-6
#Version 6 de gcc pour avoir les dernieres option de compilation en -Wall (notamment sur l'indentation trompeuse)

# Liste des executables a creer
EXEC=test_dict

CFLAGS=-Iinclude/dictionnaire/ -Iinclude/ -Wall -g
DFLAGS=-DFRANCAIS


## Zone de traitement des noms fichiers bruts (ajout de préfixes, suffixes, gestion de l'emplacement)
# Dossiers
BUILDDIR=build
SOURCEDIR=src
BINDIR=bin

# Noms de fichier
BIN=$(addprefix bin/, $(EXEC))
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
# Adapte d'une commande recuperee sur internet
OBJECTS:=$(SOURCES:$(SOURCEDIR)/%.c=$(BUILDDIR)/%.o)



## Zone de gestion des librairies
# Variable indiquant les flags de linking on indique l'emplacement ou chercher les librairies
LDFLAGS=
# Variable listant les librairies a ajouter
LIBNAME=
LDLIBS=$(addprefix -l, $(LIBNAME))



all:$(BIN)


$(BINDIR)/main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(DFLAGS) $(LDFLAGS) $(LDLIBS)


$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(DFLAGS)



## Regles de nettoyage

# Nettoie tout le repertoire : fichiers intermediaires ET executables crees
mrproper:
	@rm -rf -v $(BINDIR) $(BUILDDIR)

# Nettoie les fichiers intermediaires
clean:
	@rm -rf -v $(BUILDDIR)/*.o

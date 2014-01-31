#On purge la liste des suffixes utilise pour les roles implicites
.SUFFIXES:

#On ajoute simplements les extensions dont l'on a besoin
.SUFFIXES:.cpp .o

#Nom de l'executable
EXEC=skfcm

#Liste des fichiers sources separes par des espaces
SOURCES=main.cpp

#Liste des fichiers objets
OBJETS=$(SOURCES:%.cpp=%.o)

#Compilateur et options de compilation
CCPP=g++
CFLAGS=-Wall -ansi -pedantic -ffast-math -I /usr/X11R6/include -I ./CImg


LFLAGS= -L . -L /usr/X11R6/lib  -lpthread -lX11 -lXext -Dcimg_use_xshm  -lm

$(EXEC):$(OBJETS) Makefile
	$(CCPP) -o  $(EXEC) $(OBJETS) $(LFLAGS)
.cpp.o:
	$(CCPP) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJETS)
clear:
	rm $(EXEC)
depend:
	sed -e "/^#DEPENDANCIES/,$$ d" Makefile >dependances
	echo "#DEPENDANCIES" >> dependances
	$(CCPP) -MM $(SOURCES) >> dependances
	cat dependances >Makefile
	rm dependances

#DEPENDANCIES
main.o: main.cpp 





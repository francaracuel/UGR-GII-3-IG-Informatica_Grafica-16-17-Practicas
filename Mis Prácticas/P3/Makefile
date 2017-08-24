########################################################################
# 
# Informática Gráfica
# Grado en Ingeniería Informática
# 
# CURSO 2016-2017
# Francisco Javier Caracuel Beltrán
# 
# Makefile asociado a la práctica 3
# 
########################################################################

# Nombre de la práctica
TARGETS = practica3

SRC     = ./src
INCLUDE = ./include
LIB     = ./lib
BIN     = ./bin
OBJ     = ./obj

# Banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -I/usr/include -I$(INCLUDE)
CXXFLAGS=  -g -I/usr/include -I$(INCLUDE)

# Banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# Definicion del compilador
#
CC = g++

# Definicion de objetos
#
SRCS= $(SRC)/practica3.cc $(SRC)/escena.cc $(SRC)/ejes.cc $(SRC)/obj3D.cc $(SRC)/mesh.cc $(SRC)/tetrahedron.cc $(SRC)/cube.cc $(SRC)/diamond.cc $(SRC)/sphere.cc $(SRC)/obj_ply.cc $(SRC)/file_ply_stl.cc $(SRC)/obj_rev.cc $(SRC)/obj_rev_x.cc $(SRC)/obj_rev_y.cc $(SRC)/obj_rev_z.cc $(SRC)/dog_head.cc


# Orden que será ejecutada por defecto
#
all:	author \
	clean \
	_start \
	targets \
	_end
	    
targets:
	$(CC) -o $(BIN)/$(TARGETS) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -std=c++11

#
#
clean:
	@echo
	@echo ------------------------------------------------------------------
	@echo
	@echo Limpieza de los directorios:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*
	@echo
	@echo ------------------------------------------------------------------
	@echo

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f $(OBJ)/*.o
	rm *~
	rm -f $(BIN)/$(TARGETS)

#
#
tgz:
	rm -f $(OBJ)/*.o
	rm *~
	rm -f $(BIN)/$(TARGETS)
	tar -zcvf $(TARGETS).tgz *

author:
	@echo ------------------------------------------------------------------
	@echo
	@echo Francisco Javier Caracuel Beltrán
	@echo 
	@echo Práctica 3
	@echo
	@echo ------------------------------------------------------------------

_start:
	@echo Compilando...
	@echo
	@echo ------------------------------------------------------------------
	
_end:
	@echo ------------------------------------------------------------------
	@echo
	@echo Compilación terminada
	@echo
	@echo ------------------------------------------------------------------

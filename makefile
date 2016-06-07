#Makefile for terminal crush saga
#Author: Cristofer A. Oswald & Bruno Cesar
#Date: 06/06/2016 -> 666

CC = gcc
CFLAGS = -c
MKDIR = mkdir
SR = ./source/
O = $(SR)o/
SRCS = $(SR)main.c $(SR)saga.c $(SR)menu.c $(SR)fila_lista_ligada/fila.c
OBJS = $(O)main.o $(O)saga.o $(O)menu.o $(O)fila.o
EXE = saga

all : $(SRCS) $(EXE)

$(EXE) : $(OBJS)
	$(CC) -pg $(OBJS) -o $(EXE)

$(O)main.o : $(SR)main.c
	$(MKDIR) $(O)
	$(CC) $(CFLAGS) $(SR)main.c -o $(O)main.o

$(O)saga.o : $(SR)saga.c
	$(CC) $(CFLAGS) $(SR)saga.c -o $(O)saga.o

$(O)fila.o : $(SR)fila_lista_ligada/fila.c
	$(CC) $(CFLAGS) $(SR)fila_lista_ligada/fila.c -o $(O)fila.o

$(O)menu.o : $(SR)menu.c
	$(CC) $(CFLAGS) $(SR)menu.c -o $(O)menu.o

clean :
	rm -rf $(O)

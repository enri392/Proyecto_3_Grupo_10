#Compilación

PHONY: ALL

APP1=nw

CC=gcc

cflags=`pkg-config --cflags --libs gtk+-3.0` -lpthread -lm

ALL: 
	$(CC) $(APP1).c -o $(APP1) $(cflags) 


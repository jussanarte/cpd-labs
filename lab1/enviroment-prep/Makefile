# Variáveis
CC = gcc #Variavel para o compilador - para caso se queira mudar o compilador.
CFLAGS = -g -Wall #Opções do compilador (-g são as infos para o gdb, -Wall ativa todos os avisos);
main: list.o main.o
	$(CC) $(CFLAGS) -o main list.o main.o
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c
main.o: main.c  list.h
	$(CC) $(CFLAGS) -c main.c
clean:
	rm -f *.o main
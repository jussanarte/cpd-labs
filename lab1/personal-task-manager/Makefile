# Variáveis
CC = gcc #Variavel para o compilador - para caso se queira mudar o compilador.
CFLAGS = -g -Wall #Opções do compilador (-g são as infos para o gdb, -Wall ativa todos os avisos);
main: task_list.o main.o
	$(CC) $(CFLAGS) -o main task_list.o main.o
task_list.o: task_list.c task_list.h
	$(CC) $(CFLAGS) -c task_list.c
main.o: main.c  task_list.h
	$(CC) $(CFLAGS) -c main.c
clean:
	rm -f *.o main
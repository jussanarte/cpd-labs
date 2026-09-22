# Variáveis de Configuração
CC = mpicc
CFLAGS = -Wall -O2

# Lista de executáveis a gerar (os nomes diferem dos ficheiros .c)
TARGETS = hello sendReceive comp

# Regra padrão: compila todos os targets
all: $(TARGETS)

hello: helloWorld.c
	$(CC) $(CFLAGS) helloWorld.c -o hello

sendReceive: sendReceive.c
	$(CC) $(CFLAGS) sendReceive.c -o sendReceive

comp: comparacao.c
	$(CC) $(CFLAGS) comparacao.c -o comp

# Regra para limpar os executáveis
clean:
	rm -f $(TARGETS)

# Evita conflitos com ficheiros que tenham o mesmo nome das regras
.PHONY: all clean
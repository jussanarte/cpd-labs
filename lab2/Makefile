# Variáveis de Configuração
CC = gcc
CFLAGS = -Wall -fopenmp
LDFLAGS = -fopenmp

# Lista de executáveis a gerar (baseado nos nomes dos ficheiros .c)
TARGETS = omp1 omp2

# Regra padrão: compila todos os targets
all: $(TARGETS)

# Regra para compilar qualquer executável a partir do seu .c correspondente
# % é um wildcard (funciona como um "match" para o nome do ficheiro)
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Regra para limpar os executáveis e ficheiros temporários
clean:
	rm -f $(TARGETS)

# Evita conflitos com ficheiros que tenham o mesmo nome das regras
.PHONY: all clean
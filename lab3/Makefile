# Variáveis de Configuração
CC = gcc
CFLAGS = -Wall -O2 -fopenmp

# Lista de executáveis a gerar (baseado nos nomes dos ficheiros .c)
TARGETS = mult-sync mult-redux mult-good

# Regra padrão: compila todos os targets
all: $(TARGETS)

# Regra para compilar qualquer executável a partir do seu .c correspondente
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Regra para limpar os executáveis
clean:
	rm -f $(TARGETS)

# Evita conflitos com ficheiros que tenham o mesmo nome das regras
.PHONY: all clean
# Lab 1 — Introdução ao Ambiente Unix

Laboratório 1 de CPD: familiarização com o ciclo de desenvolvimento em C no ambiente Unix (**gcc**, **gdb**, **make**) e com a gestão de processos.

## 📜 Enunciado (resumo)

- **Objectivos**: introduzir o desenvolvimento em C no ambiente Unix e familiarizar com `gcc`, `gdb`, `make` e comandos Unix.
- **Executável**: compilar (`.c` → `.o`), ligar e gerar o executável `main`; depurar com `gdb` (breakpoints, `step`/`next`, `print`/`display`); gerar e analisar um *core dump* (segmentation fault).
- **Make**: regras, dependências (ex.: `list.h`) e alvo `clean`.
- **Exercícios**: implementar `update_terminated_process`; construir o **gestor de tarefas** — `new <prioridade> <id>`, `list <prioridade>`, `complete <id>` — com identificador único (sem espaços) e prioridade 0–5.
- **Desafio (`cpd-terminal`)**: terminal paralelo que executa e monitoriza programas em paralelo.
  - *Etapa 1*: `pathname [arg1 ... arg5]` em *background*; `exit` espera pelos filhos e reporta pid/valor devolvido.
  - *Etapa 2*: tarefa monitora (thread) que regista tempos de execução, coordenada via `numChildren` e `wait`.
  - Requisito: `Makefile` com alvo `cpd-terminal`.

## Conteúdo

### 1. `enviroment-prep/`
Programa de exemplo (listas ligadas de processos) usado para praticar compilação, debug com `gdb` e `make`. Inclui a função `update_terminated_process` (exercício proposto).

```bash
make
./main
```

### 2. `personal-task-manager/`
Gestor de tarefas pessoais em linha de comandos. Cada tarefa tem prioridade (0 a 5) e é inserida ordenada por prioridade e, em caso de empate, por data de criação mais recente.

Comandos: `new <prioridade> <id> <descrição>`, `list <prioridade>`, `complete <id>`, `update <id> <prioridade>` (extra) e `exit`.

```bash
make
./main
```

### 3. `cpd-terminal/`
**Desafio do laboratório** — terminal paralelo que executa e monitoriza programas em paralelo (Etapa 1).

```bash
make
./cpd-terminal
```

Comandos:
- `<pathname> [arg1 ... arg5]` — executa o programa indicado como processo filho em *background* (máximo 5 argumentos);
- `exit` — termina o `cpd-terminal` de forma ordeira.

A interação com o utilizador usa os comandos `fork` e `execvp`; a leitura de argumentos é feita com a biblioteca `commandlinereader`.

## Estado

- **cpd-terminal**: implementada a **Etapa 1** (execução paralela em *background*).
- **Em progresso (Etapa 2)**: tarefa monitora (thread) que registe os tempos de lançamento e terminação de cada processo filho, coordenada por uma estrutura partilhada (`numChildren`) e sincronização POSIX.
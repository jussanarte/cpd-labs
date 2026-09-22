# Lab 2 — Introdução ao OpenMP

Laboratório 2 de CPD: primeiro contacto com o **OpenMP** — directivas `parallel`, `for`, `nowait`, `barrier` e o problema de *dependências de dados* em paralelização de loops.

## 📜 Enunciado (resumo)

- **Objectivo**: introduzir o **OpenMP**.
- **Problema 1 (`omp1.c`)**: compilar com `-fopenmp`; executar com diferentes valores de `OMP_NUM_THREADS`; adicionar a cláusula `nowait` à directiva `for`; adicionar `#pragma omp barrier` — comparar saídas e explicar as diferenças.
- **Problema 2 (`omp2.c`)**: paralelizar o loop `V[i] = f(V[i], V[i+1])` com dependências (`f(x, y) = (x + y) / 2.0`):
  - a) compilar e executar a versão serial;
  - b) criar uma versão paralela simples (incorrecta) e encontrar uma execução com saída diferente da serial;
  - c) corrigir copiando o vector `V` da iteração anterior;
  - d) modificar para evitar copiar `V` em todas as iterações (implementado com *double buffering*).

## Compilar

```bash
make
```

Gera os executáveis `omp1` e `omp2`.

## Programas

### `omp1.c` — Sincronização de threads
Experiências com a cláusula `nowait` numa directiva `for` e com a directiva `barrier`.

```bash
OMP_NUM_THREADS=n ./omp1
```

### `omp2.c` — Loop interior com dependências
Paraleliza o loop `V[i] = f(V[i], V[i+1])`, em que cada iteração depende da anterior. A solução usa **double buffering** (dois vectores com papéis alternados, `V_read`/`V_write`), evitando copiar o vector em todas as iterações.

```bash
OMP_NUM_THREADS=n ./omp2
```

## Saídas (entregáveis obrigatórios)

| Ficheiro | Descrição |
|----------|-----------|
| `serial.txt` | Saída da execução da versão serial |
| `paralelo.txt` | Consolidação das execuções paralelas (antigos `paralelo1-8.txt`): execuções de `omp2` com diferentes valores de `OMP_NUM_THREADS` |

## Limpar

```bash
make clean
```
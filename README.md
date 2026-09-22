# 📖 cpd-labs

Conjunto de soluções dos **laboratórios de Computação Paralela e Distribuída** em **linguagem C**, cobrindo gestão de processos (POSIX), **OpenMP** e **MPI**, com análise de desempenho (profiling com Intel VTune).

🧪 Desenvolvido para a disciplina de **Computação Paralela e Distribuída (CPD)** do **ISPTEC**, ano lectivo 2025-26.

## 📑 Índice

- [Objetivo](#objetivo)
- [Contexto académico](#contexto-académico)
- [Funcionalidades](#funcionalidades)
- [Algoritmos e técnicas](#algoritmos-e-técnicas)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Requisitos](#requisitos)
- [Como executar](#como-executar)
- [Exemplo de execução](#exemplo-de-execução)
- [Atribuição](#atribuição)
- [Integrantes](#integrantes)
- [Licença](#licença)

## 🎯 Objetivo

Aplicar, na prática, os modelos de programação paralela e distribuída estudados na disciplina:

- 🔀 **Processos e concorrência** — criação de processos filhos com `fork`/`execvp` em *background* (terminal paralelo `cpd-terminal`);
- 🧵 **OpenMP** — paralelização de loops com `parallel for`, controlo de sincronização (`nowait`, `barrier`) e resolução de dependências de dados (*double buffering*);
- 📊 **Análise de desempenho** — identificação de *hotspots* e gargalos com o **Intel VTune Profiler** (análises de *Hotspots* e *Threading*);
- 📡 **MPI** — comunicação ponto-a-ponto, operações colectivas (`MPI_Bcast`) e medição de **latência** e **largura de banda** numa rede.

Cada laboratório inclui um `README.md` próprio, com um resumo do enunciado, objectivos, compilação e execução.

## 🏫 Contexto académico

| Campo | Valor |
|---|---|
| Instituição | Instituto Superior Politécnico de Tecnologias e Ciências (ISPTEC) |
| Coordenação | Engenharia Informática — Departamento de Engenharias e Tecnologias |
| Curso | Licenciatura em Engenharia Informática |
| Cadeira | Computação Paralela e Distribuída (CPD) |
| Ano letivo | 2025/2026 |
| Autor | Jussana Paim |
| Ambiente de desenvolvimento | Linux via WSL |

## ⚙️ Funcionalidades

| Laboratório | Descrição |
|---|---|
| `lab1` | Ambiente Unix (gcc/gdb/make); gestor de tarefas de prioridade 0–5; terminal paralelo `cpd-terminal` que executa programas em *background* (comandos `<pathname> [args...]` e `exit`) |
| `lab2` | Programas OpenMP `omp1` (experiências com `nowait`/`barrier`) e `omp2` (paralelização de loop com dependências usando *double buffering*); saídas `serial.txt` e `paralelo.txt` (entregáveis obrigatórios) |
| `lab3` | Três implementações de multiplicação de matrizes (`mult-sync`, `mult-redux`, `mult-good`) para análise comparativa de desempenho/sincronização no VTune |
| `lab4` | Programas MPI: `helloWorld` (saudações), `sendReceive` (latência/largura de banda em anel) e `comparacao` (envio individual vs `MPI_Bcast`) |

> ✅ `cpd-terminal` implementa a **Etapa 1** do desafio; a **Etapa 2** (tarefa monitora com `pthreads` para registo de tempos de execução) está planeada como próximo passo.

## 🧮 Algoritmos e técnicas

| Técnica | Onde | Aspecto-chave |
|---|---|---|
| `fork` + `execvp` (processos) | `lab1/cpd-terminal` | Execução paralela em *background* |
| Listas simplesmente ligadas | `lab1/enviroment-prep`, `lab1/personal-task-manager` | Gestão de processos/tarefas com inserção ordenada |
| `#pragma omp parallel for`, `nowait`, `barrier` | `lab2`, `lab3` | Paralelização e sincronização de threads |
| *Double buffering* (`V_read`/`V_write`) | `lab2/omp2.c` | Elimina dependências entre iterações sem copiar o vector |
| `MPI_Send`/`MPI_Recv` e `MPI_Bcast` | `lab4` | Comunicação ponto-a-ponto vs operação colectiva |

## 📁 Estrutura do repositório

```
cpd-labs/
├── README.md
├── lab1/
│   ├── enviroment-prep/        # Ex. gcc/gdb/make + update_terminated_process
│   ├── personal-task-manager/  # Gestor de tarefas (new/list/complete/update)
│   ├── cpd-terminal/           # Terminal paralelo (desafio, Etapa 1)
│   └── README.md
├── lab2/
│   ├── omp1.c, omp2.c          # Programas OpenMP
│   ├── serial.txt, paralelo.txt  # Saídas (entregáveis obrigatórios)
│   ├── Makefile
│   └── README.md
├── lab3/
│   ├── mult-sync.c, mult-redux.c, mult-good.c
│   ├── Makefile
│   └── README.md
└── lab4/
    ├── helloWorld.c, sendReceive.c, comparacao.c
    ├── Makefile
    └── README.md
```

## 🧰 Requisitos

- **Linux** (desenvolvido em WSL)
- `gcc`, `gdb`, `make`
- OpenMP (`libgomp`) — compilação com `-fopenmp`
- MPI (`mpicc`, `mpirun`) — ex.: Open MPI

## 🚀 Como executar

Cada laboratório é autocontido; consulte o `README.md` respectivo. Resumo:

| Laboratório | Compilar | Executar |
|---|---|---|
| lab1 (enviroment-prep) | `make` | `./main` |
| lab1 (personal-task-manager) | `make` | `./main` |
| lab1 (cpd-terminal) | `make` | `./cpd-terminal` |
| lab2 | `make` | `OMP_NUM_THREADS=n ./omp1` |
| lab3 | `make` | `./mult-good` |
| lab4 | `make` | `mpirun -np 4 ./sendReceive 1000` |

> 💡 Execute a partir da raiz do laboratório respectivo para que os `Makefile` sejam encontrados.

## 🖥️ Exemplo de execução

Sessão do `cpd-terminal` a executar o programa `fibonacci` em *background* e terminar de forma ordeira:

```
cpd-terminal> fibonacci 20
cpd-terminal> fibonacci 21
cpd-terminal> exit
```

Análise de *threading* no Intel VTune — comparação entre `mult-sync`, `mult-redux` e `mult-good`:

```
$ vtune -collect threading ./mult-good
```

## 🙏 Atribuição

Código baseado no material do Prof. João Costa (ISPTEC), autor dos enunciados e de parte do código-fornecido (ex.: `commandlinereader`, `list.c`, `omp1.c`, `omp2.c`, `sendReceive.c`), adaptado e estendido para este repositório.

## 👥 Integrantes

| Nome | Notas |
|---|---|
| Jussana Paim | Autor e autor das adaptações |

## 📄 Licença

Sem licença formal definida (material académico). O resumo do enunciado de cada laboratório encontra-se no `README.md` respectivo.
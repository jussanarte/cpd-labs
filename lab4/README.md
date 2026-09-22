# Lab 4 — Programação com MPI

Laboratório 4 de CPD: programação com **MPI** (Message Passing Interface) — comunicação ponto-a-ponto, operações colectivas e medição de latência/largura de banda.

## 📜 Enunciado (resumo)

- **Objectivo**: introduzir a programação com **MPI**.
- **Preliminares**: criar o programa de saudações (`helloWorld` — "O Processo `<id>` envia cumprimentos a partir da máquina `<node-id>`!").
- **`sendReceive.c`**: examinar o código, compilá-lo e executá-lo com valores diferentes do parâmetro de entrada; modificá-lo para medir experimentalmente a **latência** e a **largura de banda** da rede.
- **`comparacao.c`**: comparar o desempenho entre o **broadcast** de um grande array para todos os nós e o **envio individual** (mensagens ponto-a-ponto).

## Programas

### `helloWorld.c`
Cada processo imprime uma saudação com o seu `rank` e o nome da máquina.

### `sendReceive.c`
Passa uma mensagem de 1 MB por todos os processos em anel (ponto-a-ponto) durante `n` rondas e calcula a **latência** e a **largura de banda** médias.

### `comparacao.c`
Compara o desempenho entre **enviar** um array de 1 MB do processo 0 para cada nó individualmente (`MPI_Send`/`MPI_Recv`) e usar **`MPI_Bcast`** (operação colectiva optimizada).

## Compilar

```bash
make
```

Gera os executáveis `hello`, `sendReceive` e `comp` (usando `mpicc`).

> Limpar: `make clean`

## Executar

```bash
mpirun -np 4 ./hello
mpirun -np 4 ./sendReceive 1000
mpirun -np 4 ./comp
```

Exemplo de uso de `comparacao.c` com >= 2 processos:

```
=== COMPARAÇÃO DE DESEMPENHO ===
Processos: P | Tamanho: 1000000 bytes
Tempo Individual: ... seg
Tempo Broadcast:  ... seg
Melhoria: ...x mais rápido com Bcast
```

## Referências

- Open MPI — <https://www.open-mpi.org>
- MPI Forum — <https://www.mpi-forum.org>
- Documentação das rotinas MPI — <http://www.mcs.anl.gov/research/projects/mpi/www/www3>
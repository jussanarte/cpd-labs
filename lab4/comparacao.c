/*
    Name: Comparação de Desempenho (Individual vs Broadcast)
    Description: Compara o tempo de envio de um grande array para todos os nós.
    Updated by: Jussana Paim
    Updated at: 2026-05-12
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int id, p, i;
    double t_inicio, t_individual, t_bcast;
    
    // Tamanho da mensagem: 1 milhão de caracteres (aprox. 1 MB)
    long int msg_size = 1000000;
    char *msg = (char *)malloc(msg_size * sizeof(char));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (p < 2) {
        if (id == 0) printf("Execute com pelo menos 2 processos.\n");
        free(msg);
        MPI_Finalize();
        return 0;
    }

    // --- PARTE 1: ENVIO INDIVIDUAL (PONTO-A-PONTO) ---
    MPI_Barrier(MPI_COMM_WORLD); // Sincroniza todos antes de começar
    t_inicio = MPI_Wtime();

    if (id == 0) {
        // O mestre envia para cada escravo individualmente
        for (i = 1; i < p; i++) {
            MPI_Send(msg, msg_size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Cada escravo recebe do mestre
        MPI_Recv(msg, msg_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    t_individual = MPI_Wtime() - t_inicio;


    // --- PARTE 2: BROADCAST (COLETIVA) ---
    MPI_Barrier(MPI_COMM_WORLD); // Sincroniza todos novamente
    t_inicio = MPI_Wtime();

    // A função coletiva envia do Rank 0 para todos de forma otimizada
    MPI_Bcast(msg, msg_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    t_bcast = MPI_Wtime() - t_inicio;


    // --- RESULTADOS ---
    if (id == 0) {
        printf("\n=== COMPARAÇÃO DE DESEMPENHO ===\n");
        printf("Processos: %d | Tamanho: %ld bytes\n", p, msg_size);
        printf("Tempo Individual: %.6f seg\n", t_individual);
        printf("Tempo Broadcast:  %.6f seg\n", t_bcast);
        
        if (t_bcast > 0) {
            printf("Melhoria: %.2fx mais rápido com Bcast\n", t_individual / t_bcast);
        }
        printf("================================\n");
    }

    free(msg);
    MPI_Finalize();
    return 0;
}
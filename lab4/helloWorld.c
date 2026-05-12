#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    // Inicialização do ambiente MPI
    MPI_Init(&argc, &argv);

    // Recebe o número total de processos
    /* int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); */

    // Recebe o rank do processo
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Busca o nome do processador
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Cada processo imprime uma mensagem de saudação
    printf("O Processo %d envia cumprimentos a partir da máquina %s!\n", world_rank, processor_name);

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}
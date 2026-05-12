/*
	Name: Send and Receive Message
	Copyright: 2021-22
	Author: Prof. Joao Costa
	Date: 13/05/22 10:28
	Description:
	Simple experience to understand the Message Passing Interface.

	UPDATED BY: Jussana Paim
	UPDATED AT: 2026-05-11
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

	// Variável para armazenar o status da comunicação
	MPI_Status status;
	int id, p, i, rounds;
	// Variável para medir o tempo gasto na comunicação
	double secs;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// Verifica se o número de processos é maior que 1
	if (argc != 2)
	{
		if (!id)
			printf("Command line: %s <n-rounds>\n", argv[0]);
		MPI_Finalize();
		exit(1);
	}
	rounds = atoi(argv[1]);

	// Sincroniza os processos antes de iniciar a comunicação
	MPI_Barrier(MPI_COMM_WORLD);
	secs = -MPI_Wtime();

	// Loop para enviar e receber mensagens entre os processos
	for (i = 0; i < rounds; i++)
	{
		if (!id)
		{
			// O processo 0 inicia a comunicação enviando uma mensagem para o processo 1
			MPI_Send(&i, 1, MPI_INT, 1, i, MPI_COMM_WORLD);
			MPI_Recv(&i, 1, MPI_INT, p - 1, i, MPI_COMM_WORLD, &status);
		}
		else
		{
			// Os processos intermediários recebem a mensagem do processo anterior e enviam para o próximo processo
			MPI_Recv(&i, 1, MPI_INT, id - 1, i, MPI_COMM_WORLD, &status);
			MPI_Send(&i, 1, MPI_INT, (id + 1) % p, i, MPI_COMM_WORLD);
		}
	}

	// Sincroniza os processos após a comunicação e calcula o tempo gasto
	MPI_Barrier(MPI_COMM_WORLD);
	secs += MPI_Wtime();

	// O processo 0 imprime o tempo gasto e a média por envio/recebimento
	if (!id)
	{
		printf("Rounds= %d, N Processes = %d, Time = %12.6f sec,\n",
			   rounds, p, secs);
		printf("Average time per Send/Recv = %6.2f us\n",
			   secs * 1e6 / (2 * rounds * p));
	}
	MPI_Finalize();
	return 0;
}

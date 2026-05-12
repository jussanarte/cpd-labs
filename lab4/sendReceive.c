/*
	Name: Send and Receive Message
	Copyright: 2021-22
	Author: Prof. Joao Costa
	Date: 13/05/22 10:28
	Description:
	Simple experience to understand the Message Passing Interface.

	UPDATED BY: Jussana Paim
	UPDATED AT: 2026-05-12
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
	//Tamanho da mensagem a ser enviada/recebida (1 MB)
	long int msg_size = 1024 * 1024;
	char *msg = (char *)malloc(msg_size * sizeof(char)); // Aloca memória para a mensagem

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
			MPI_Send(msg, msg_size, MPI_CHAR, 1, i, MPI_COMM_WORLD);
			MPI_Recv(msg, msg_size, MPI_CHAR, p - 1, i, MPI_COMM_WORLD, &status);
		}
		else
		{
			// Os processos intermediários recebem a mensagem do processo anterior e enviam para o próximo processo
			MPI_Recv(msg, msg_size, MPI_CHAR, id - 1, i, MPI_COMM_WORLD, &status);
			MPI_Send(msg, msg_size, MPI_CHAR, (id + 1) % p, i, MPI_COMM_WORLD);
		}
	}

	// Sincroniza os processos após a comunicação e calcula o tempo gasto
	MPI_Barrier(MPI_COMM_WORLD);
	secs += MPI_Wtime();

	// O processo 0 imprime o tempo gasto e a média por envio/recebimento
	if (!id)
	{
		double total_hops = (double)rounds * p;
        double avg_hop_time = secs / total_hops;
        // Largura de banda: Tamanho da msg / tempo de um salto
        double bandwidth = (msg_size / (1024.0 * 1024.0)) / avg_hop_time;

		printf("Rounds = %d\nN Processes = %d\nTime = %.6f sec,\n", rounds, p, secs);
		printf("Average time per Send/Recv = %6.2f us\n", secs * 1e6 / (2 * rounds * p));
		printf("Average bandwidth = %6.2f MB/s\n", bandwidth);
		printf("Average latency = %6.2f us\n", avg_hop_time * 1e6);
	}
	free(msg); // Libera a memória alocada para a mensagem
	MPI_Finalize();
	return 0;
}

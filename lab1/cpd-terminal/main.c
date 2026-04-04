#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "headers/commandlinereader.h"

#define MAX_ARGS 7
#define BUFFER_SIZE 100

int main() {
    char *args[MAX_ARGS];
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("cpd-terminal> ");
        fflush(stdout);

        int numArgs = readLineArguments(args, MAX_ARGS, buffer, BUFFER_SIZE);

        if (numArgs < 0) {
            printf("\n");
            break;
        }

        if (numArgs == 0) {
            continue;
        }

        // comando exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        int pid = fork();

        if (pid < 0) {
            perror("fork error");
            continue;
        }

        if (pid == 0) {
            // processo filho
            execvp(args[0], args);
            

            // só chega aqui se der erro
            perror("Error executing");
            exit(1);
        }
        // processo pai NÃO faz wait (background)
    }

    return 0;
}
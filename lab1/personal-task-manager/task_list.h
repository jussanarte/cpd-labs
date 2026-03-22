#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Estrutura que representa uma Tarefa */
typedef struct task {
    int id;
    char description[100];
    int priority;           /* 0 (Baixa) a 5 (Alta) */
    time_t created_at;
    struct task *next;
} task_t;

/* Estrutura que controla a lista */
typedef struct {
    task_t *first;
} list_t;

/* Protótipos das funções */
list_t* new_task_lst();
void destroy_task_lst(list_t *list);
void insert_new_task(list_t *list, int id, char *desc, int priority);
void update_task_priority(list_t *list, int id, int new_priority);
void print_task_lst(list_t *list, int min_priority);
void complete_task(list_t *list, int id);

#endif


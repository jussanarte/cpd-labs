/*
 * list.c - implementation of the integer list functions 
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"



list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
}


void lst_destroy(list_t *list)
{
	struct lst_iitem *item, *nextitem;

	item = list->first;
	while (item != NULL){
		nextitem = item->next;
		free(item);
		item = nextitem;
	}
	free(list);
}


void insert_new_process(list_t *list, int pid, time_t starttime)
{
	lst_iitem_t *item;

	item = (lst_iitem_t *) malloc (sizeof(lst_iitem_t));
	item->pid = pid;
	item->starttime = starttime;
	item->endtime = 0;
	item->next = list->first;
	list->first = item;
}


void update_terminated_process(list_t *list, int pid, time_t endtime)
{
    // 1. Verificação de segurança: a lista existe?
    if (list == NULL || list->first == NULL) {
        return; 
    }

    lst_iitem_t *item = list->first;

    // 2. Percorrer a lista
    while (item != NULL) {
        if (item->pid == pid) {
            item->endtime = endtime;
            printf("Process with pid %d updated with endtime.\n", pid);
            return; // Encontrou? Atualiza e sai da função imediatamente
        }
        item = item->next;
    }

    // 3. Se chegou aqui, percorreu tudo e não encontrou o PID
    printf("Process with pid %d not found in list.\n", pid);
}

void lst_print(list_t *list)
{
	lst_iitem_t *item;

	printf("Process list with start and end time:\n");
	item = list->first;
	//while(1){ /* use it only to demonstrate gdb potencial */
	while (item != NULL){
		printf("Pid: %d\tStartime: %s", item->pid, ctime(&(item->starttime)));
		printf("\tEndtime: %s", ctime(&(item->endtime)));
		item = item->next;
	}
	printf("-- end of list.\n");
}

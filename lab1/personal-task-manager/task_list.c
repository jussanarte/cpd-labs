#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task_list.h"

list_t* new_task_lst() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (list) list->first = NULL;
    return list;
}

void insert_new_task(list_t *list, int id, char *desc, int priority) {
   task_t *new_node = (task_t *) malloc(sizeof(task_t));

   if(new_node != NULL){
    new_node->id = id;
    strncpy(new_node->description, desc, 99);

    new_node->priority = priority;
    new_node->created_at = time(NULL);

    task_t *curr = list->first;
    task_t *prev = NULL;

    // Procura a posição correta
    while (curr != NULL) {
        if (priority > curr->priority) break;
        if (priority == curr->priority && new_node->created_at >= curr->created_at) break;
        
        prev = curr;
        curr = curr->next;
    }

    new_node->next = curr;
    if (prev == NULL) list->first = new_node;
    else prev->next = new_node;
   }else{
    puts("[ERROR]: Memory Allocation failed.");
   }
    
}

void update_task_priority(list_t *list, int id, int new_priority) {
    if (list == NULL) return;

    task_t *item = list->first;
    while (item != NULL) {
        if (item->id == id) {
            item->priority = new_priority;
            printf("[SUCCESS]: Task %d updated to priority level %d.\n", id, new_priority);
            return;
        }
        item = item->next;
    }
    printf("[INFO]: Task %d not found.\n", id);
}

void print_task_lst(list_t *list, int min_priority) {
    if (list == NULL || list->first == NULL) {
        puts("[INFO]: Empty task list.");
        return;
    }

    task_t *item = list->first;
    int found = 0;

    printf("\n--- TASK MANAGER (Min Priority: %d) ---\n", min_priority);
    while (item != NULL) {
        // Aplica o filtro solicitado
        if (item->priority >= min_priority) {
            printf("ID: %d | Priority: [%d] | Description: %s\n", 
                   item->id, item->priority, item->description);
            found = 1;
        }
        item = item->next;
    }
    
    if (!found){
        printf("No tasks found with priority >= %d\n", min_priority);
    }
    printf("-------------------------\n");
}

void destroy_task_lst(list_t *list) {
    task_t *item = list->first;
    while (item != NULL) {
        task_t *next = item->next;
        free(item);
        item = next;
    }
    free(list);
}

void complete_task(list_t *list, int id) {
    if (list == NULL || list->first == NULL) {
        printf("[INFO]: Non-existent Task.");
        return;
    }

    task_t *curr = list->first;
    task_t *prev = NULL;

    // Procura o ID na lista
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    // Se chegou ao fim e não encontrou
    if (curr == NULL) {
        puts("[INFO]: Non-existent Task.");
        return;
    }

    // Se for o primeiro da lista
    if (prev == NULL) {
        list->first = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr);
    printf("[SUCCESS]: Task %d removed.\n", id);
}
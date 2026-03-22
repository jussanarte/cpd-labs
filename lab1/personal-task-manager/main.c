#include <stdio.h>
#include <string.h>
#include "task_list.h"

int main() {
    list_t *tasks = new_task_lst();
    char command[20];
    int id, priority;
    char desc[100];

    puts("--- TASK MANAGER CONSOLE ---");
    puts("Comandos: new, list, complete, update, exit");

    while (1) {
        printf("\n>> ");
        if (scanf("%s", command) == EOF) break;

        if (strcmp(command, "new") == 0) {
            if (scanf("%d %d %[^\n]", &priority, &id, desc) == 3) {
                insert_new_task(tasks, id, desc, priority);
                printf("[SUCCESS]: Task %d added.\n", id);
            } else {
                puts("[ERROR]: Invalid arguments for 'new'.");
            }
        } 
        else if (strcmp(command, "list") == 0) {
            if (scanf("%d", &priority) == 1) {
                print_task_lst(tasks, priority);
            } else {
                puts("[ERROR]: Invalid priority for 'list'.");
            }
        } 
        else if (strcmp(command, "complete") == 0) {
            if (scanf("%d", &id) == 1) {
                complete_task(tasks, id); 
            } else {
                puts("[ERROR]: Invalid ID for 'complete'.");
            }
        } 
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else if (strcmp(command, "update") == 0) {
            if (scanf("%d %d", &id, &priority) == 2) {
                update_task_priority(tasks, id, priority);
                printf("[SUCCESS]: Task priority %d updated.\n", id);
            } else {
                puts("[ERROR]: Invalid arguments for 'update'.");
            }
        } 
        else {
            printf("[ERROR]: Command '%s' not found.\n", command);
            while (getchar() != '\n'); 
        }
    }

    destroy_task_lst(tasks);
    return 0;
}
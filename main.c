#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "task.h"
#include "file.h"

void showMenu() {
    printf("\n===== TASK MANAGER =====\n");
    printf("1. Add task\n");
    printf("2. Delete task\n");
    printf("3. Display tasks\n");
    printf("4. Sort tasks\n");
    printf("5. Save tasks to file\n");
    printf("6. Load tasks from file\n");
    printf("0. Exit\n");
    printf("Choose: ");
}

int main() {
    Task* head = NULL;
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            int id;
            char title[100];
            int important;

            printf("ID: ");
            scanf("%d", &id);
            printf("Title: ");
            scanf(" %[^\n]", title);
            printf("Important? (1 = yes, 0 = no): ");
            scanf("%d", &important);

            // Satifies Requirement 4: Data Structure Implementation
            Task* newTask = createTask(id, title, important);
            newTask->next = head;
            head = newTask;

        } else if (choice == 2) {
            int id;
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            deleteTask(&head, id);

        } else if (choice == 3) {
            displayTasks(head);

        } else if (choice == 4) {
            sortTasks(head);
            printf("Tasks sorted.\n");

        } else if (choice == 5) {
            saveTasksToFile("tasks.txt", head);

        } else if (choice == 6) {
            freeList(head);
            head = NULL;
            loadTasksFromFile("tasks.txt", &head);
        }

    } while (choice != 0);

    freeList(head);
    return 0;
}

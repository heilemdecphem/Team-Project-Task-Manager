#include <stdio.h>
#include <stdlib.h>
#include "file.h"

// Satisfies Requirement 5: File I/O Operations
bool saveTasksToFile(const char* filename, Task* head) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Cannot open file to save");
        return false;
    }

    Task* temp = head;
    while (temp != NULL) {
        fprintf(fp, "%d;%s;%d;%d\n",
                temp->id,
                temp->title,
                temp->isImportant,
                temp->order);
        temp = temp->next;
    }

    fclose(fp);
    return true;
}

bool loadTasksFromFile(const char* filename, Task** head) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Cannot open file to load");
        return false;
    }

    int id, isImportant, order;
    char title[100];

    while (fscanf(fp, "%d;%99[^;];%d;%d\n",
                  &id, title, &isImportant, &order) == 4) {

        Task* newTask = createTask(id, title, isImportant);
        newTask->order = order;
        newTask->next = *head;
        *head = newTask;
    }

    fclose(fp);
    return true;
}

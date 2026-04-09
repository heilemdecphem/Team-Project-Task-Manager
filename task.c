#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "task.h"

static int currentOrder = 0;

Task* createTask(int id, char* title, bool isImportant) {
    // allocate memory for 
    // Satisfies Requirement 3: Dynamic Memory Management
    Task* newTask = malloc(sizeof(Task));
    if (newTask == NULL) {
        perror("Cannot create new tasks!\n");
        exit(EXIT_FAILURE);
    }

    // fill in info
    newTask->id = id;
    strcpy(newTask->title, title);
    newTask->isImportant = isImportant;
    newTask->order = currentOrder++;
    newTask->next = NULL;
    
    // return task
    return newTask;
}

void deleteTask(Task** head, int id) {
    Task* temp = *head, *prev = NULL;
    
    // if temp at the top
    while(temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    // keep finding
    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // if item not found
    if (temp == NULL) {
        printf("Failed to find task.\n");
        return;
    }

    // if found the item
    prev->next = temp->next;
    free(temp);
}

void displayTasks(Task* head) {
    // opening message
    printf("Current tasks for you today:\n");
    
    Task* temp = head;
    int item = 1;
    
    // going through the list and print each temp
    while (temp != NULL) {
        printf("Task %d: %s", item, temp->title);
        item++;
        
        // notify user if this item is important
        if (temp->isImportant) {
            printf("(IMPORTANT!)\n");
        }
        printf("\n");

        temp = temp->next;
    }
}

Task* searchTask(Task* head, int id) {
    Task* temp = head;
    
    // go through each task
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    // if task not found
    if (temp == NULL) {
        printf("Task not found.\n");
        exit;
    }
    
    // if found
    return temp;
}

// helper function that compares whether the two tasks should swap order based on (primary) importance and (secondary) when it was 
// 1 if yes, 0 if no
int shouldSwap(Task* a, Task* b) {
    
    // if b is impportant than a
    if (a->isImportant < b->isImportant) {
        return 1;
    }
    
    // if b is as important as a but b is added earlier than a
    if (a->isImportant == b->isImportant && a->order > b->order) {
        return 1;
    }

    // otherwise no need to swap
    return 0;
}

// swap the data instead of the whole struct
// simple swap function: temp = a, a = b, b = temp.
void swapTaskData(Task* a, Task* b) {
    int tempId = a->id;
    char tempTitle[100];
    strcpy(tempTitle, a->title);
    bool tempImportant = a->isImportant;
    int tempOrder = a->order;

    a->id = b->id;
    strcpy(a->title, b->title);
    a->isImportant = b->isImportant;
    a->order = b->order;

    b->id = tempId;
    strcpy(b->title, tempTitle);
    b->isImportant = tempImportant;
    b->order = tempOrder;
}

// sort task
void sortTasks(Task* head) {
    Task* i;
    Task* j;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (shouldswap(i, j)) {
                swapTaskData(i, j);
            }
        }
    }
}

// free memory
void freeList(Task* head) {
    Task* temp = NULL;
    
    // go through each task
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

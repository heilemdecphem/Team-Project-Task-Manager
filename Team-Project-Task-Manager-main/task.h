#ifndef TASK_H
#define TASK_H

#include <stdbool.h>

// Struct Definition
// Satifies Requirement 2: Advanced Pointers & Structs
typedef struct Task {
    int id;
    char title[100];
    bool isImportant;
    int order;
    struct Task* next;
} Task;


// Core Function Prototypes
Task* createTask(int id, char* title, bool isImportant); // Create a new task node
void deleteTask(Task** head, int id); // Delete a task by ID
void displayTasks(Task* head); // Display all tasks
Task* searchTask(Task* head, int id); // Search for a task by ID
void sortTasks(Task* head); // Sort tasks (important first)
void freeList(Task* head); // Free entire task list

#endif

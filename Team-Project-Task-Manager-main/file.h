#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include "task.h"

bool saveTasksToFile(const char* filename, Task* head);
bool loadTasksFromFile(const char* filename, Task** head);

#endif

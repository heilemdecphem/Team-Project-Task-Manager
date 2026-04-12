#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "task.h"
#include "file.h"

// Helper to count tasks in list
int countTasks(Task* head) {
    int count = 0;
    Task* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Helper to check if task exists
bool taskExists(Task* head, int id) {
    Task* temp = head;
    while (temp != NULL) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

// Helper to check if sorted by importance
bool isSortedByImportance(Task* head) {
    if (head == NULL || head->next == NULL) return true;
    Task* temp = head;
    while (temp->next != NULL) {
        if (!temp->isImportant && temp->next->isImportant) return false;
        temp = temp->next;
    }
    return true;
}

void print_result(int case_num, const char* description, bool passed) {
    printf("Test Case %d: %s -> %s\n", case_num, description, passed ? "PASS" : "FAIL");
}

int main() {
    printf("\n========== TASK MANAGER TEST RESULTS ==========\n\n");
    
    bool all_passed = true;
    bool result;

    // ========== TEST CASE 1 ==========
    {
        Task* head = NULL;
        Task* t1 = createTask(101, "Finish report", true);
        t1->next = head;
        head = t1;
        Task* t2 = createTask(102, "Call client", false);
        t2->next = head;
        head = t2;
        
        result = (countTasks(head) == 2) && taskExists(head, 101) && taskExists(head, 102);
        print_result(1, "Add and display 2 tasks (one important, one not)", result);
        if (!result) all_passed = false;
        freeList(head);
    }

    // ========== TEST CASE 2 ==========
    {
        Task* head = NULL;
        Task* t1 = createTask(101, "Finish report", true);
        t1->next = head;
        head = t1;
        Task* t2 = createTask(102, "Call client", false);
        t2->next = head;
        head = t2;
        
        deleteTask(&head, 101);
        deleteTask(&head, 999);  // Should not crash
        
        result = (countTasks(head) == 1) && !taskExists(head, 101) && taskExists(head, 102);
        print_result(2, "Delete existing task (101 removed, 102 remains)", result);
        if (!result) all_passed = false;
        freeList(head);
    }

    // ========== TEST CASE 3 ==========
    {
        Task* head = NULL;
        Task* t1 = createTask(1, "Task A", false);
        t1->next = head;
        head = t1;
        Task* t2 = createTask(2, "Task B", true);
        t2->next = head;
        head = t2;
        Task* t3 = createTask(3, "Task C", false);
        t3->next = head;
        head = t3;
        
        sortTasks(head);
        
        result = isSortedByImportance(head);
        print_result(3, "Sort tasks (important tasks appear first)", result);
        if (!result) all_passed = false;
        freeList(head);
    }

    // ========== TEST CASE 4 ==========
    {
        Task* head = NULL;
        Task* t1 = createTask(201, "Task One", true);
        t1->next = head;
        head = t1;
        Task* t2 = createTask(202, "Task Two", false);
        t2->next = head;
        head = t2;
        
        int original_count = countTasks(head);
        saveTasksToFile("test.txt", head);
        freeList(head);
        head = NULL;
        
        loadTasksFromFile("test.txt", &head);
        int loaded_count = countTasks(head);
        
        result = (loaded_count == original_count);
        print_result(4, "Save and load tasks from file", result);
        if (!result) all_passed = false;
        
        remove("test.txt");
        freeList(head);
    }

    // ========== TEST CASE 5 ==========
    {
        Task* head = NULL;
        Task* t1 = createTask(301, "Submit assignment", true);
        t1->next = head;
        head = t1;
        
        Task* found = searchTask(head, 301);
        Task* not_found = searchTask(head, 999);
        
        result = (found != NULL && found->id == 301) && (not_found == NULL);
        print_result(5, "Search for task by ID (found and not found)", result);
        if (!result) all_passed = false;
        freeList(head);
    }

    printf("\n==============================================\n");
    printf("OVERALL RESULT: %s\n", all_passed ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    printf("==============================================\n\n");
    
    return all_passed ? 0 : 1;
}
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "PD.h"


PD_TUPLE* new_PD_TUPLE(int projectId, int dependsOn) {
    PD_TUPLE* this = malloc(sizeof(PD_TUPLE));
    if (this) {
        this->projectId = projectId;
        this->dependsOn = dependsOn;
        this->next = NULL;
    }
    return this;
}

void PD_TUPLE_print(PD_TUPLE* this) {
    if (this) {
        printf("Project ID: %d, Depends On: %d\n", this->projectId, this->dependsOn);
    }
}

void PD_HASHTABLE_print(const PD_HASHTABLE table) {
    printf("--------PD hashtable:--------\n");
    for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        PD_TUPLE* current = table[i];
        while (current != NULL) {
            PD_TUPLE_print(current);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


int h_PD_projectId(int projectId) {
    return projectId % PD_HASHTABLE_SIZE;
}

void PD_insert(PD_TUPLE* t, PD_HASHTABLE R) {
    int i = h_PD_projectId(t->projectId);
    PD_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && p->dependsOn == t->dependsOn) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
}

//This insert method will print out the table table after insertion
void PD_insert2(PD_TUPLE* t, PD_HASHTABLE R) {
    printf("Inserting entries: [ProjectID: %d, Depends On: %d]\n",
           t->projectId, t->dependsOn);
    int i = h_PD_projectId(t->projectId);
    PD_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && p->dependsOn == t->dependsOn) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
    PD_HASHTABLE_print(R);
}



void PD_lookup(PD_TUPLE* X, PD_HASHTABLE R) {
    printf("PD_lookup results for Project ID: %d, Depends On: %d\n", X->projectId, X->dependsOn);
    bool found = false; 

    for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
        for (PD_TUPLE* current = R[i]; current != NULL; current = current->next) {
            if ((X->projectId == -1 || current->projectId == X->projectId) &&
                (X->dependsOn == -1 || current->dependsOn == X->dependsOn)) {
                PD_TUPLE_print(current);
                found = true;
            }
        }
    }

    if (!found) {
        printf("No results found for Project ID: %d, Depends On: %d\n", X->projectId, X->dependsOn);
    }
}


void PD_delete(PD_TUPLE* X, PD_HASHTABLE R) {
    printf("Deleting entries matching: [ProjectID: %d, Depends On: %d]\n",
           X->projectId, X->dependsOn);

    bool found = false;
    for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
        PD_TUPLE **prev = &R[i];
        PD_TUPLE *current = R[i];

        while (current != NULL) {
            if ((X->projectId == -1 || current->projectId == X->projectId) &&
                (X->dependsOn == -1 || current->dependsOn == X->dependsOn)) {
                *prev = current->next; 
                free(current);          
                current = *prev;       
                found = true;          
            } else {
                prev = &current->next; 
                current = current->next;
            }
        }
    }
    
    if (!found) {
        printf("No matching entries found.\n"); 
    }
    PD_HASHTABLE_print(R); 
}


void PD_HASHTABLE_init(PD_HASHTABLE R) {
    for (int i = 0; i < PD_HASHTABLE_SIZE; i++) {
        R[i] = NULL;
    }
}

void PD_generate(PD_HASHTABLE R) {
    PD_TUPLE* t;
    t = new_PD_TUPLE(99863, 72278);
    PD_insert(t, R);

    t = new_PD_TUPLE(57849, 63653);
    PD_insert(t, R);
    
    t = new_PD_TUPLE(57849, 31687);
    PD_insert(t, R);
    t = new_PD_TUPLE(31687, 57849);
    PD_insert(t, R);
    t = new_PD_TUPLE(63653, 23169);
    PD_insert(t, R);
    PD_HASHTABLE_print(R);
}


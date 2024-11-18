#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "PM.h"


PM_TUPLE* new_PM_TUPLE(int projectId, char* manager_ssn) {
    PM_TUPLE* this = malloc(sizeof(PM_TUPLE));
    if (this) {
        this->projectId = projectId;
        strncpy(this->manager_ssn, manager_ssn, sizeof(this->manager_ssn) - 1);
        this->manager_ssn[sizeof(this->manager_ssn) - 1] = '\0';
        this->next = NULL;
    }
    return this;
}

void PM_TUPLE_print(PM_TUPLE* this) {
    if (this) {
        printf("Project ID: %d, Manager SSN: %s\n", this->projectId, this->manager_ssn);
    }
}


void PM_HASHTABLE_print(const PM_HASHTABLE table) {
    printf("--------PM hashtable:--------\n");
    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        PM_TUPLE* current = table[i];
        while (current != NULL) {
            PM_TUPLE_print(current);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

int h_PM_projectId(int projectId) {
    return projectId % PM_HASHTABLE_SIZE;
}

void PM_insert(PM_TUPLE* t, PM_HASHTABLE R) {
    int i = h_PM_projectId(t->projectId);
    PM_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->manager_ssn, t->manager_ssn) == 0) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
}

//This insert method will print out the table table after insertion
void PM_insert2(PM_TUPLE* t, PM_HASHTABLE R) {
    printf("Deleting entries: [ProjectID: %d, Manager SSN: %s]\n",
       t->projectId, t->manager_ssn);
    int i = h_PM_projectId(t->projectId);
    PM_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->manager_ssn, t->manager_ssn) == 0) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
    PM_HASHTABLE_print(R);
}


void PM_lookup(PM_TUPLE* X, PM_HASHTABLE R) {
    PM_TUPLELIST Z[PM_HASHTABLE_SIZE];
    bool found = false;

    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        Z[i] = NULL;
    }

    int matchProjectId = (X->projectId == -1);
    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        PM_TUPLE** lastNextPtr = &Z[i];
        for (PM_TUPLE* current = R[i]; current != NULL; current = current->next) {
            int matchPID = (matchProjectId || current->projectId == X->projectId);
            int matchMSSN = (X->manager_ssn[0] == '*' || strcmp(current->manager_ssn, X->manager_ssn) == 0);

            if (matchPID && matchMSSN) {
                PM_TUPLE* match = new_PM_TUPLE(current->projectId, current->manager_ssn);
                if (match != NULL) {
                    *lastNextPtr = match;
                    lastNextPtr = &match->next; 
                    found = true;
                }
            }
        }
    }

    printf("PM_lookup results for: ");
    PM_TUPLE_print(X);
    printf("\n");

    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        for (PM_TUPLE* current = Z[i]; current != NULL;) {
            PM_TUPLE* temp = current;
            current = current->next;
            PM_TUPLE_print(temp);
            free(temp); 
        }
        if (Z[i] != NULL) {
            printf("\n");
        }
    }

    if (!found) {
        printf("No results found.\n");
    }
}



void PM_delete(PM_TUPLE* X, PM_HASHTABLE R) {
    printf("Deleting entries matching: [ProjectID: %d, Manager SSN: %s]\n",
           X->projectId, X->manager_ssn);

    bool found = false;
    int matchProjectId = (X->projectId == -1); 
    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        PM_TUPLE **prev = &R[i]; 
        PM_TUPLE *current = R[i];

        while (current != NULL) {
            int matchPid = (matchProjectId || current->projectId == X->projectId);
            int matchMSSN = (X->manager_ssn[0] == '*' || strcmp(current->manager_ssn, X->manager_ssn) == 0);

            if (matchPid && matchMSSN) {
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
    PM_HASHTABLE_print(R); 
}


void PM_HASHTABLE_init(PM_HASHTABLE R) {
    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        R[i] = NULL;
    }
}


void PM_generate(PM_HASHTABLE R) {
    PM_TUPLE* t;
    t = new_PM_TUPLE(57849, "101-85-4521");
    PM_insert(t, R);
    t = new_PM_TUPLE(23169, "319-97-1535");
    PM_insert(t, R);
    t = new_PM_TUPLE(99863, "210-86-2988");
    PM_insert(t, R);
    t = new_PM_TUPLE(63653, "101-85-4521");
    PM_insert(t, R);
    t = new_PM_TUPLE(31687, "251-12-6815");
    PM_insert(t, R);
    t = new_PM_TUPLE(72278, "210-86-2988");
    PM_insert(t, R);
    PM_HASHTABLE_print(R);
}

       




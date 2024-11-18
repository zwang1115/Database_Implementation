#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "PDA.h"


PDA_TUPLE* new_PDA_TUPLE(int projectId, char* department, char* account) {
    PDA_TUPLE* this = malloc(sizeof(PDA_TUPLE));
    if (this) {
        this->projectId = projectId;
        strncpy(this->department, department, sizeof(this->department) - 1);
        this->department[sizeof(this->department) - 1] = '\0';
        strncpy(this->account, account, sizeof(this->account) - 1);
        this->account[sizeof(this->account) - 1] = '\0';
        this->next = NULL;
    }
    return this;
}


void PDA_TUPLE_print(PDA_TUPLE* this) {
    if (this) {
        printf("Project ID: %d, Department: %s, Account: %s\n", this->projectId, this->department, this->account);
    }
}



void PDA_HASHTABLE_print(const PDA_HASHTABLE table) {
    printf("--------PDA hashtable:--------\n");
    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        PDA_TUPLE* current = table[i];
        while (current != NULL) {
            PDA_TUPLE_print(current);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

int h_PDA_projectId(int projectId) {
    return projectId % PDA_HASHTABLE_SIZE;
}

void PDA_insert(PDA_TUPLE* t, PDA_HASHTABLE R) {
    int i = h_PDA_projectId(t->projectId);
    PDA_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->department, t->department) == 0 && strcmp(p->account, t->account) == 0) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
}

//This insert method will print out the table table after insertion
void PDA_insert2(PDA_TUPLE* t, PDA_HASHTABLE R) {
    printf("Inserting entries: Project ID: %d, Department: %s, Account: %s\n", 
           t->projectId, t->department, t->account);
    int i = h_PDA_projectId(t->projectId);
    PDA_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->department, t->department) == 0 && strcmp(p->account, t->account) == 0) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;

    PDA_HASHTABLE_print(R);

}


void PDA_lookup(PDA_TUPLE* X, PDA_HASHTABLE R) {
    PDA_TUPLELIST Z[PDA_HASHTABLE_SIZE];
    bool found = false;  

    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        Z[i] = NULL;
    }
    int matchProjectId = (X->projectId == -1);

    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        PDA_TUPLE** lastNextPtr = &Z[i]; 
        for (PDA_TUPLE* current = R[i]; current != NULL; current = current->next) {
            int matchPID = (matchProjectId || current->projectId == X->projectId);
            int matchDep = (X->department[0] == '*' || strcmp(current->department, X->department) == 0);
            int matchAcc = (X->account[0] == '*' || strcmp(current->account, X->account) == 0);

            if (matchPID && matchDep && matchAcc) {
                PDA_TUPLE* match = new_PDA_TUPLE(current->projectId, current->department, current->account);
                if (match != NULL) {
                    *lastNextPtr = match; 
                    lastNextPtr = &match->next;  
                    found = true;
                }
            }
        }
    }

    printf("PDA_lookup results for: ");
    PDA_TUPLE_print(X);
    printf("\n");

    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        for (PDA_TUPLE* current = Z[i]; current != NULL;) {
            PDA_TUPLE* temp = current;
            current = current->next;
            PDA_TUPLE_print(temp);
            free(temp);  
        }
        if (Z[i] != NULL) {
            printf("\n");
        } else if (i == PDA_HASHTABLE_SIZE - 1 && !found) {
            printf("No results found.\n");
        }
    }
}



void PDA_delete(PDA_TUPLE* X, PDA_HASHTABLE R) {
    printf("Deleting entries matching: Project ID: %d, Department: %s, Account: %s\n", 
           X->projectId, X->department, X->account);

    bool found = false; 

    int matchProjectId = (X->projectId == -1);
    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        PDA_TUPLE **prev = &R[i];
        PDA_TUPLE *current = R[i];

        while (current != NULL) {
            int matchPid = (matchProjectId || current->projectId == X->projectId);
            int matchDep = (X->department[0] == '*' || strcmp(current->department, X->department) == 0);
            int matchAcc = (X->account[0] == '*' || strcmp(current->account, X->account) == 0);

            if (matchPid && matchDep && matchAcc) {
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

    PDA_HASHTABLE_print(R);
}


void PDA_HASHTABLE_init(PDA_HASHTABLE R) {
    for (int i = 0; i < PDA_HASHTABLE_SIZE; i++) {
        R[i] = NULL;
    }
}

void PDA_generate(PDA_HASHTABLE R) {
    PDA_TUPLE* t;
    t = new_PDA_TUPLE(63653, "Marketing", "A082");
    PDA_insert(t, R);

    t = new_PDA_TUPLE(99863, "Operations", "N903");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(57849, "Support", "C764");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(99863, "Facilities", "J690");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(72278, "Facilities", "M857");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(31687, "Facilities", "R837");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(57849, "Marketing", "N903");
    PDA_insert(t, R);
    t = new_PDA_TUPLE(23169, "Operations", "J690");
    PDA_insert(t, R);
    PDA_HASHTABLE_print(R);
}


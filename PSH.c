#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "PSH.h"


PSH_TUPLE* new_PSH_TUPLE(int projectId, char* SSN, char* hours) {
    PSH_TUPLE* this = malloc(sizeof(PSH_TUPLE));
    if (this) {
        this->projectId = projectId;
        strncpy(this->SSN, SSN, sizeof(this->SSN) - 1);
        this->SSN[sizeof(this->SSN) - 1] = '\0';
        strncpy(this->hours, hours, sizeof(this->hours) - 1);
        this->hours[sizeof(this->hours) - 1] = '\0';
        this->next = NULL;
    }
    return this;
}

void PSH_TUPLE_print(PSH_TUPLE* this) {
    if (this) {
        printf("Project ID: %d, SSN: %s, Hours: %s\n", this->projectId, this->SSN, this->hours);
    }
}

void PSH_HASHTABLE_print(const PSH_HASHTABLE table) {
    printf("--------PSH hashtable:--------\n");
    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        PSH_TUPLE* current = table[i];
        while (current != NULL) {
            PSH_TUPLE_print(current);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


int h_PSH_projectId(int projectId) {
    return projectId % PSH_HASHTABLE_SIZE;
}

void PSH_insert(PSH_TUPLE* t, PSH_HASHTABLE R) {
    int i = h_PSH_projectId(t->projectId);
    PSH_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->SSN, t->SSN) == 0 && strcmp(p->hours, t->hours)) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
}

//This insert method will print out the table table after insertion
void PSH_insert2(PSH_TUPLE* t, PSH_HASHTABLE R) {
    printf("Inserting entries: Project ID: %d, SSN: %s, Hours: %s\n",
           t->projectId, t->SSN, t->hours);
    int i = h_PSH_projectId(t->projectId);
    PSH_TUPLE* p = R[i];
    while (p != NULL) {
        if (p->projectId == t->projectId && strcmp(p->SSN, t->SSN) == 0 && strcmp(p->hours, t->hours)) {
            printf("The tuple is already in the table\n");
            return;
        }
        p = p->next;
    }
    t->next = R[i];
    R[i] = t;
    PSH_HASHTABLE_print(R);
}

void PSH_lookup(PSH_TUPLE* X, PSH_HASHTABLE R) {
    PSH_TUPLELIST Z[PSH_HASHTABLE_SIZE];
    bool found = false; 

    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        Z[i] = NULL;
    }
    int matchProjectId = (X->projectId == -1);
 
    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        PSH_TUPLE** lastNextPtr = &Z[i]; 
        for (PSH_TUPLE* current = R[i]; current != NULL; current = current->next) {
            int matchPID = (matchProjectId || current->projectId == X->projectId);
            int matchSSN = (X->SSN[0] == '*' || strcmp(current->SSN, X->SSN) == 0);
            int matchHour = (X->hours[0] == '*' || strcmp(current->hours, X->hours) == 0);

            if (matchPID && matchSSN && matchHour) {
                PSH_TUPLE* match = new_PSH_TUPLE(current->projectId, current->SSN, current->hours);
                if (match != NULL) {
                    *lastNextPtr = match;  
                    lastNextPtr = &match->next; 
                    found = true;
                }
            }
        }
    }

    printf("PSH_lookup results for: ");
    PSH_TUPLE_print(X);
    printf("\n");

    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        for (PSH_TUPLE* current = Z[i]; current != NULL;) {
            PSH_TUPLE* temp = current;
            current = current->next;
            PSH_TUPLE_print(temp);
            free(temp); 
        }
        if (Z[i] != NULL) {
            printf("\n");
        } else if (i == PSH_HASHTABLE_SIZE - 1 && !found) {
            printf("No results found.\n");
        }
    }
}



void PSH_delete(PSH_TUPLE* X, PSH_HASHTABLE R) {
    printf("Deleting entries matching: Project ID: %d, SSN: %s, Hours: %s\n",
           X->projectId, X->SSN, X->hours);

    bool found = false;  

    int matchProjectId = (X->projectId == -1);
    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        PSH_TUPLE **prev = &R[i];
        PSH_TUPLE *current = R[i];

        while (current != NULL) {
            int matchPID = (matchProjectId || current->projectId == X->projectId);
            int matchSSN = (X->SSN[0] == '*' || strcmp(current->SSN, X->SSN) == 0);
            int matchHour = (X->hours[0] == '*' || strcmp(current->hours, X->hours) == 0);

            if (matchPID && matchSSN && matchHour) {
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

    PSH_HASHTABLE_print(R);
}


void PSH_HASHTABLE_init(PSH_HASHTABLE R) {
    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        R[i] = NULL;
    }
}


void PSH_generate(PSH_HASHTABLE R) {
    PSH_TUPLE* t;
    t = new_PSH_TUPLE(57849, "251-12-6815", "5.5");
    PSH_insert(t, R);

    t = new_PSH_TUPLE(23169, "319-97-1535", "6.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(63653, "021-08-4448", "4.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(72278, "210-86-2988", "7.5");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(31687, "251-12-6815", "4.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(99863, "319-97-1535", "6.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(23169, "098-54-7473", "9.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(99863, "101-85-4521", "5.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(31687, "101-85-4521", "4.0");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(57849, "101-85-4521", "7.5");
    PSH_insert(t, R);
    t = new_PSH_TUPLE(99863, "098-54-7473", "4.5");
    PSH_insert(t, R);
    PSH_HASHTABLE_print(R);
}

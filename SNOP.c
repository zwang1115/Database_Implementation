#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "SNOP.h"


SNOP_TUPLE* new_SNOP_TUPLE(char* ssn, char* name, char* office, char* phone) {
    SNOP_TUPLE* this = malloc(sizeof(SNOP_TUPLE));
    if (this) {
        strcpy(this->ssn, ssn);
        strcpy(this->name, name);
        strcpy(this->office, office);
        strcpy(this->phone, phone);
        this->next = NULL;
    }
    return this;
}

void SNOP_TUPLE_print(SNOP_TUPLE* this) {
    if (this) { // check if it's not null first 
        printf("SSN: %s, Name: %s, Office: %s, Phone: %s\n",
               this->ssn, this->name, this->office, this->phone);
    }
}

int h_SNOP_ssn(SNOP_TUPLE* t) {
    const char* key = t->ssn;
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % SNOP_HASHTABLE_SIZE;
}



void SNOP_insert(SNOP_TUPLE* t, SNOP_HASHTABLE R) {
    int i = h_SNOP_ssn(t); 
    SNOP_TUPLE* p = R[i]; 
    while (p != NULL) { 
        if (strcmp(p->ssn, t->ssn) == 0 &&
        strcmp(p->name, t->name) == 0 &&
        strcmp(p->office, t->office) == 0 &&
        strcmp(p->phone, t->phone) == 0 ) { 
            printf("The tuple is already in the table\n");
        }
        p = p->next; 
    }
    t->next = R[i];
    R[i] = t;
}

//This insert method will print out the table table after insertion
void SNOP_insert2(SNOP_TUPLE* t, SNOP_HASHTABLE R) {
    printf("Inserting entries: [SSN: %s, Name: %s, Office: %s, Phone: %s]\n",
           t->ssn, t->name, t->office, t->phone);
    int i = h_SNOP_ssn(t); 
    SNOP_TUPLE* p = R[i]; 
    while (p != NULL) { 
        if (strcmp(p->ssn, t->ssn) == 0 &&
        strcmp(p->name, t->name) == 0 &&
        strcmp(p->office, t->office) == 0 &&
        strcmp(p->phone, t->phone) == 0 ) { 
            printf("The tuple is already in the table\n");
        }
        p = p->next; 
    }
    t->next = R[i];
    R[i] = t;
    SNOP_HASHTABLE_print(R);
}

void SNOP_lookup(SNOP_TUPLE* X, SNOP_HASHTABLE R) {
    SNOP_TUPLELIST Z[SNOP_HASHTABLE_SIZE];
    bool found = false; 

    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        Z[i] = NULL;
    }

    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        SNOP_TUPLE** lastNextPtr = &Z[i];
        for (SNOP_TUPLE* current = R[i]; current != NULL; current = current->next) {
            int matchSSN = (X->ssn[0] == '*' || strcmp(current->ssn, X->ssn) == 0);
            int matchName = (X->name[0] == '*' || strcmp(current->name, X->name) == 0);
            int matchOffice = (X->office[0] == '*' || strcmp(current->office, X->office) == 0);
            int matchPhone = (X->phone[0] == '*' || strcmp(current->phone, X->phone) == 0);

            if (matchSSN && matchName && matchOffice && matchPhone) {
                SNOP_TUPLE* match = new_SNOP_TUPLE(current->ssn, current->name, current->office, current->phone);
                if (match != NULL) {
                    *lastNextPtr = match; 
                    lastNextPtr = &match->next; 
                    found = true; 
                }
            }
        }
    }

    printf("SNOP_lookup results for: ");
    SNOP_TUPLE_print(X);
    printf("\n");

    if (!found) {
        printf("No results found.\n");
    } else {
        for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
            for (SNOP_TUPLE* current = Z[i]; current != NULL;) {
                SNOP_TUPLE* temp = current;
                current = current->next;
                SNOP_TUPLE_print(temp);
                free(temp); 
            }
            if (Z[i] != NULL) {
                printf("\n");
            }
        }
    }
}



void SNOP_HASHTABLE_print(const SNOP_HASHTABLE table) {
    printf("--------SNOP hashtable:--------\n");
    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        SNOP_TUPLE* current = table[i];
        while (current != NULL) {
            SNOP_TUPLE_print(current);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}


void SNOP_delete(SNOP_TUPLE* X, SNOP_HASHTABLE R) {
    printf("Deleting entries matching: [SSN: %s, Name: %s, Office: %s, Phone: %s]\n",
           X->ssn, X->name, X->office, X->phone);

    bool found = false; 
    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        SNOP_TUPLE **prev = &R[i];
        SNOP_TUPLE *current = R[i];

        while (current != NULL) {
            int matchSSN = (X->ssn[0] == '*' || strcmp(current->ssn, X->ssn) == 0);
            int matchName = (X->name[0] == '*' || strcmp(current->name, X->name) == 0);
            int matchOffice = (X->office[0] == '*' || strcmp(current->office, X->office) == 0);
            int matchPhone = (X->phone[0] == '*' || strcmp(current->phone, X->phone) == 0);

            if (matchSSN && matchName && matchOffice && matchPhone) {
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
    SNOP_HASHTABLE_print(R);
}



void SNOP_HASHTABLE_init(SNOP_HASHTABLE R) {
    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        R[i] = NULL;
    }
}

void SNOP_generate(SNOP_HASHTABLE R) {
    SNOP_TUPLE* t;
    t = new_SNOP_TUPLE("972-06-2473", "H. Kim", "Dewey 402", "851-3472");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("251-12-6815", "E. Price", "Hutchison 754", "896-4408");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("021-08-4448", "M. Ruiz", "CSB 571", "360-1897");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("319-97-1535", "H. Kim", "Morey 758", "704-9520");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("210-86-2988", "J. Jackson", "Lattimore 879", "952-9418");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("098-54-7473", "R. Roberts", "Harkness 156", "314-9972");
    SNOP_insert(t, R);
    t = new_SNOP_TUPLE("101-85-4521", "M. Ruiz", "Hylan 525", "470-6491");
    SNOP_insert(t, R);
    SNOP_HASHTABLE_print(R);
}


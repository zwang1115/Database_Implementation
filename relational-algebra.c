#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "relational-algebra.h"

JOINED_TUPLE* new_JOINED_TUPLE(int projectId, char* manager_ssn, char* department, char* account) {
    JOINED_TUPLE* this = malloc(sizeof(JOINED_TUPLE));
    if (this) {
        this->projectId = projectId;
        strncpy(this->manager_ssn, manager_ssn, sizeof(this->manager_ssn) - 1);
        this->manager_ssn[sizeof(this->manager_ssn) - 1] = '\0';
        strncpy(this->department, department, sizeof(this->department) - 1);
        this->department[sizeof(this->department) - 1] = '\0';
        strncpy(this->account, account, sizeof(this->account) - 1);
        this->account[sizeof(this->account) - 1] = '\0';
        this->next = NULL;
    }
    return this;
}
int hash_joined(int projectId) {
    return projectId % JOINED_HASHTABLE_SIZE;
}

void print_JOINED_HASHTABLE(JOINED_HASHTABLE table) {
    if (!table) {
        printf("Table is NULL.\n");
        return;
    }
    printf("Joined Table Contents:\n");
    for (int i = 0; i < JOINED_HASHTABLE_SIZE; i++) {
        JOINED_TUPLE* tuple = (table)[i];
        if (tuple) {
            printf("Bucket %d:\n", i);
            while (tuple) {
                printf("  ProjectId: %d, Manager SSN: %s, Department: %s, Account: %s\n",
                       tuple->projectId, tuple->manager_ssn, tuple->department, tuple->account);
                tuple = tuple->next;
            }
        }
    }
}


// Function to insert a new tuple into the joined hashtable
void insert_JOINED_TUPLE(JOINED_HASHTABLE table, int projectId, char* manager_ssn, char* department, char* account) {
    int index = hash_joined(projectId);
    JOINED_TUPLE* new_tuple = new_JOINED_TUPLE(projectId, manager_ssn, department, account);
    new_tuple->next = table[index];
    table[index] = new_tuple;
}

void select_PSH_ProjectId(PSH_HASHTABLE psh_table) {
    bool found = false;
    for (int i = 0; i < PSH_HASHTABLE_SIZE; i++) {
        for (PSH_TUPLE* t = psh_table[i]; t != NULL; t = t->next) { // Correct traversal of the linked list in each bucket
            if (t->projectId == 99863) {
                found = true;
                printf("ProjectId: %d, SSN: %s, Hours: %s\n", t->projectId, t->SSN, t->hours);
            }
        }
    }
    if (!found) {
        printf("No tuple found with ProjectId 99863.\n");
    }
}

void project_SNOP_Name(SNOP_HASHTABLE snop_table) {
    bool printed[256] = {0}; // Map to track printed names based on first letter
    printf("Projected Names from SNOP:\n");
    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        for (SNOP_TUPLE* tuple = snop_table[i]; tuple != NULL; tuple = tuple->next) {
            unsigned char index = (unsigned char)tuple->name[0];  // Cast to unsigned char to use as index safely
            if (!printed[index]) {  // Check if the name with this starting letter has been printed
                printf("Name: %s\n", tuple->name);
                printed[index] = true;  // Mark as printed
            }
        }
    }
}

JOINED_HASHTABLE create_joined_hashtable() {
    JOINED_HASHTABLE table = malloc(JOINED_HASHTABLE_SIZE * sizeof(JOINED_TUPLE*));
    if (table) {
        for (int i = 0; i < JOINED_HASHTABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }
    return table;
}

JOINED_HASHTABLE join_PM_PDA(PM_HASHTABLE pm_table, PDA_HASHTABLE pda_table) {
    JOINED_HASHTABLE joined_table = create_joined_hashtable();
    if (!joined_table) {
        printf("Failed to allocate memory for joined table.\n");
        return NULL;
    }

    for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
        for (PM_TUPLE* pm = pm_table[i]; pm; pm = pm->next) {
            int hash_index = h_PM_projectId(pm->projectId);
            for (PDA_TUPLE* pda = pda_table[hash_index]; pda; pda = pda->next) {
                if (pda->projectId == pm->projectId) {
                    insert_JOINED_TUPLE(joined_table, pm->projectId, pm->manager_ssn, pda->department, pda->account);
                }
            }
        }
    }
    return joined_table;
}


void allOperations(PM_HASHTABLE pm_table, PDA_HASHTABLE pda_table) {
    JOINED_HASHTABLE joined_table = join_PM_PDA(pm_table, pda_table);
    for (int i = 0; i < JOINED_HASHTABLE_SIZE; i++) {
        for (JOINED_TUPLE* jt = joined_table[i]; jt != NULL; jt = jt->next) {
            if (strcmp(jt->manager_ssn, "210-86-2988") == 0) {
                printf("Department: %s, Account: %s\n", jt->department, jt->account);
            }
        }
    } 
}







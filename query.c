#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "relational-algebra.h"

void firstQuery(SNOP_HASHTABLE snop_table, PSH_HASHTABLE psh_table) {
    printf("Q1: How many hours does Name work on project ProjectId? ");
    printf("\n");
    char inputName[50];
    char inputBuffer[50];
    int inputId; 

    while (true) {
        printf("Enter Name (type 'stop' to exit): ");
        if (!fgets(inputName, sizeof(inputName), stdin)) continue;
        inputName[strcspn(inputName, "\n")] = 0;  
        if (strcmp(inputName, "stop") == 0) break;

         printf("Enter ProjectId (type 'stop' to exit): ");
        if (!fgets(inputBuffer, sizeof(inputBuffer), stdin)) continue;
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;
        if (strcmp(inputBuffer, "stop") == 0) break;

        inputId = atoi(inputBuffer); 

        bool found = false;

    for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
        for (SNOP_TUPLE* snop = snop_table[i]; snop != NULL; snop = snop->next) {
            if (strcmp(snop->name, inputName) == 0) {
                // use ssn to look up hours for projectId 
                for (int j = 0; j < PSH_HASHTABLE_SIZE; j++) {
                    for (PSH_TUPLE* psh = psh_table[j]; psh != NULL; psh = psh->next) {
                        if (psh->projectId == inputId && strcmp(psh->SSN, snop->ssn) == 0) {
                            printf("%s works %s hours on project %d.\n", inputName, psh->hours, inputId);
                            found = true;
                        }
                    }
                }
            }
        }
    }

    if (!found) {
        printf("No hours found for %s on project %d.\n", inputName, inputId);
     }
    
    }
}





void secondQuery(PDA_HASHTABLE pda_table, PM_HASHTABLE pm_table, SNOP_HASHTABLE snop_table) {
    printf("Q2: What is the manager’s SSN of projects involving Name from Department using Account?");
    printf("\n");
    char inputName[50];
    char inputDep[50];
    char inputAcc[20];

    while (true) {
        printf("Enter Name (type 'stop' to exit): ");
        if (!fgets(inputName, sizeof(inputName), stdin)) continue;
        inputName[strcspn(inputName, "\n")] = 0; 
        if (strcmp(inputName, "stop") == 0) break;

        printf("Enter Department (type 'stop' to exit): ");
        if (!fgets(inputDep, sizeof(inputDep), stdin)) continue;
        inputDep[strcspn(inputDep, "\n")] = 0;
        if (strcmp(inputDep, "stop") == 0) break;

        printf("Enter Account (type 'stop' to exit): ");
        if (!fgets(inputAcc, sizeof(inputAcc), stdin)) continue;
        inputAcc[strcspn(inputAcc, "\n")] = 0;
        if (strcmp(inputAcc, "stop") == 0) break;

        bool found = false;
        for (int i = 0; i < SNOP_HASHTABLE_SIZE; i++) {
            for (SNOP_TUPLE* snop = snop_table[i]; snop != NULL; snop = snop->next) {
                if (strcmp(snop->name, inputName) == 0) {
                    for (int j = 0; j < PDA_HASHTABLE_SIZE; j++) {
                        for (PDA_TUPLE* pda = pda_table[j]; pda != NULL; pda = pda->next) {
                            if (strcmp(pda->department, inputDep) == 0 && strcmp(pda->account, inputAcc) == 0) {
                                for (int k = 0; k < PM_HASHTABLE_SIZE; k++) {
                                    for (PM_TUPLE* pm = pm_table[k]; pm != NULL; pm = pm->next) {
                                        if (pm->projectId == pda->projectId) {
                                            printf("Manager's SSN for project involving %s from %s using %s is %s\n",
                                                   inputName, inputDep, inputAcc, pm->manager_ssn);
                                            found = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!found) {
            printf("No manager's SSN found for the specified Name, Department, and Account.\n");
        }
    }
}
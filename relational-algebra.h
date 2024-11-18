#include "SNOP.h"
#include "PSH.h"
#include "PM.h"
#include "PDA.h"
#include "PD.h"

#ifndef RELATIONAL_ALGEBRA_H
#define RELATIONAL_ALGEBRA_H



#define JOINED_HASHTABLE_SIZE 11

// Define JOINED_TUPLE and JOINED_HASHTABLE here
typedef struct JOINED_TUPLE JOINED_TUPLE;
typedef struct JOINED_TUPLE *JOINED_TUPLELIST;
struct JOINED_TUPLE {
    int projectId;
    char manager_ssn[12];
    char department[50];
    char account[20];
    JOINED_TUPLELIST next;
};
typedef JOINED_TUPLE** JOINED_HASHTABLE;

extern void project_SNOP_Name(SNOP_HASHTABLE snop_table);
extern void select_PSH_ProjectId(PSH_HASHTABLE psh_table);
extern JOINED_HASHTABLE join_PM_PDA(PM_HASHTABLE pm_table, PDA_HASHTABLE pda_table);
extern void print_JOINED_HASHTABLE(JOINED_HASHTABLE table);
extern void allOperations(PM_HASHTABLE pm_table, PDA_HASHTABLE pda_table);


#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "relational-algebra.h"
#include "query.h"
#include "SNOP.h"
#include "PSH.h"
#include "PM.h"
#include "PDA.h"
#include "PD.h"


int main() {
    PD_HASHTABLE pd_table;
    PD_HASHTABLE_init(pd_table);
    PD_generate(pd_table);

    PDA_HASHTABLE pda_table;
    PDA_HASHTABLE_init(pda_table);
    PDA_generate(pda_table);

    PM_HASHTABLE pm_table;
    PM_HASHTABLE_init(pm_table);
    PM_generate(pm_table);

    PSH_HASHTABLE psh_table;
    PSH_HASHTABLE_init(psh_table);
    PSH_generate(psh_table);

    SNOP_HASHTABLE snop_table;
    SNOP_HASHTABLE_init(snop_table);
    SNOP_generate(snop_table);

    printf("\n");
    // part 1
    printf("---------------------TESTING PART 1---------------------\n\n");
    printf("*****Testing(1.a)*****\n");
    PSH_lookup(new_PSH_TUPLE(99863, "319-97-1535", "*"), psh_table);
    printf("*****Testing(1.b)*****\n");
    SNOP_lookup(new_SNOP_TUPLE("*", "H. Kim", "*", "*"), snop_table);
    printf("*****Testing(1.c)*****\n");
    PD_lookup(new_PD_TUPLE(12345, 67890), pd_table);
    printf("*****Testing(1.d)\n");
    PM_delete(new_PM_TUPLE(63653, "101-85-4521"), pm_table);
    printf("*****Testing(1.e)*****\n");
    PDA_delete(new_PDA_TUPLE(72278, "Facilities", "P123"), pda_table);
    printf("*****Testing(1.f)*****\n");
    PDA_delete(new_PDA_TUPLE(72278, "*", "*"), pda_table);
    printf("*****Testing(1.g)*****\n");
    PD_insert2(new_PD_TUPLE(23169, 57849), pd_table);
    printf("*****Testing(1.h)*****\n");
    PD_insert2(new_PD_TUPLE(57849, 31687), pd_table);
    
    printf("\n\n");
    //part 2
    firstQuery(snop_table, psh_table);
    secondQuery(pda_table, pm_table, snop_table);


    //part3
    printf("---------------------TESTING PART 3---------------------\n\n");
    printf("Results for 'σProjectId=99863(PSH)':\n");
    select_PSH_ProjectId(psh_table);
    printf("\n");
    printf("Results for 'πName(SNOP)':\n");
    project_SNOP_Name(snop_table);
    printf("\n");
    printf("Results for 'PM ▷◁ PDA':\n");
    print_JOINED_HASHTABLE(join_PM_PDA(pm_table, pda_table));
    printf("Results for 'πDepartment,Account(σManagerSSN=“210-86-2988”(PM ▷◁ PDA))':\n");
    allOperations(pm_table, pda_table);


    return 0;
}

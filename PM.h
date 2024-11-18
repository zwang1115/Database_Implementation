#ifndef PM_H
#define PM_H

#define PM_HASHTABLE_SIZE 11

typedef struct PM_TUPLE *PM_TUPLELIST;
struct PM_TUPLE {
    int projectId;
    char manager_ssn[12];
    PM_TUPLELIST next;
};

typedef struct PM_TUPLE PM_TUPLE;
typedef PM_TUPLELIST PM_HASHTABLE[PM_HASHTABLE_SIZE];

PM_TUPLE* new_PM_TUPLE(int projectId, char* manager_ssn);

extern int h_PM_projectId(int projectId);

extern void PM_TUPLE_print(struct PM_TUPLE* t);

extern void PM_insert(PM_TUPLE* t, PM_HASHTABLE R);

extern void PM_insert2(PM_TUPLE* t, PM_HASHTABLE R);

extern void PM_lookup(PM_TUPLE* X, PM_HASHTABLE R);

extern void PM_delete(PM_TUPLE* X, PM_HASHTABLE R);

extern void PM_HASHTABLE_print(const PM_HASHTABLE table);

extern void PM_HASHTABLE_init(PM_HASHTABLE R);

extern void PM_generate(PM_HASHTABLE R);

#endif
#ifndef PD_H
#define PD_H
#define PD_HASHTABLE_SIZE 11

typedef struct PD_TUPLE *PD_TUPLELIST;
struct PD_TUPLE {
    int projectId;
    int dependsOn;
    PD_TUPLELIST next;
};

typedef struct PD_TUPLE PD_TUPLE;
typedef PD_TUPLELIST PD_HASHTABLE[PD_HASHTABLE_SIZE];

extern PD_TUPLE* new_PD_TUPLE(int projectId, int dependsOn);

extern int h_PD_projectId(int projectId);

extern void PD_TUPLE_print(struct PD_TUPLE* t);

extern void PD_insert(PD_TUPLE* t, PD_HASHTABLE R);
extern void PD_insert2(PD_TUPLE* t, PD_HASHTABLE R);

extern void PD_lookup(PD_TUPLE* X, PD_HASHTABLE R);

extern void PD_delete(PD_TUPLE* X, PD_HASHTABLE R);

extern void PD_HASHTABLE_print(const PD_HASHTABLE table);

extern void PD_HASHTABLE_init(PD_HASHTABLE R);

extern void PD_generate(PD_HASHTABLE R);

#endif
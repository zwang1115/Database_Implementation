#ifndef PDA_H
#define PDA_H
#define PDA_HASHTABLE_SIZE 11

typedef struct PDA_TUPLE *PDA_TUPLELIST;
struct PDA_TUPLE {
    int projectId;
    char department[50];
    char account[20];
    PDA_TUPLELIST next;
};

typedef struct PDA_TUPLE PDA_TUPLE;
typedef PDA_TUPLELIST PDA_HASHTABLE[PDA_HASHTABLE_SIZE];

extern PDA_TUPLE* new_PDA_TUPLE(int projectId, char* department, char* account);

extern int h_PDA_projectId(int projectId);

extern void PDA_TUPLE_print(struct PDA_TUPLE* t);

extern void PDA_insert(PDA_TUPLE* t, PDA_HASHTABLE R);

extern void PDA_insert2(PDA_TUPLE* t, PDA_HASHTABLE R);

extern void PDA_lookup(PDA_TUPLE* X, PDA_HASHTABLE R);

extern void PDA_delete(PDA_TUPLE* X, PDA_HASHTABLE R);

extern void PDA_HASHTABLE_print(const PDA_HASHTABLE table);

extern void PDA_HASHTABLE_init(PDA_HASHTABLE R);

extern void PDA_generate(PDA_HASHTABLE R);

#endif
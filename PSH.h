#ifndef PSH_H
#define PSH_H
#define PSH_HASHTABLE_SIZE 11

typedef struct PSH_TUPLE *PSH_TUPLELIST;
struct PSH_TUPLE {
    int projectId;
    char SSN[12];
    char hours[4];
    PSH_TUPLELIST next;
};

typedef struct PSH_TUPLE PSH_TUPLE;
typedef PSH_TUPLELIST PSH_HASHTABLE[PSH_HASHTABLE_SIZE];

extern PSH_TUPLE* new_PSH_TUPLE(int projectId, char* SSN, char* hours);

extern int h_PSH_projectId(int projectId);

extern void PSH_TUPLE_print(struct PSH_TUPLE* t);

extern void PSH_insert(PSH_TUPLE* t, PSH_HASHTABLE R);

extern void PSH_insert2(PSH_TUPLE* t, PSH_HASHTABLE R);

extern void PSH_lookup(PSH_TUPLE* X, PSH_HASHTABLE R);

extern void PSH_delete(PSH_TUPLE* X, PSH_HASHTABLE R);

extern void PSH_HASHTABLE_print(const PSH_HASHTABLE table);

extern void PSH_HASHTABLE_init(PSH_HASHTABLE R);

extern void PSH_generate(PSH_HASHTABLE R);

#endif
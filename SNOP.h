#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SNOP_H
#define SNOP_H
#define SNOP_HASHTABLE_SIZE 11

typedef struct SNOP_TUPLE *SNOP_TUPLELIST;
struct SNOP_TUPLE {
    char ssn[12];	
    char name[30];
    char office[50];
    char phone[9];	
    SNOP_TUPLELIST next;
};


typedef struct SNOP_TUPLE SNOP_TUPLE;

typedef SNOP_TUPLELIST SNOP_HASHTABLE[SNOP_HASHTABLE_SIZE];

extern SNOP_TUPLE* new_SNOP_TUPLE(char* ssn, char* name, char* office, char* phone);

extern int h_SNOP_ssn(SNOP_TUPLE* t);

extern void SNOP_TUPLE_print(struct SNOP_TUPLE* t);

extern void SNOP_insert(SNOP_TUPLE* t, SNOP_HASHTABLE R);

extern void SNOP_insert2(SNOP_TUPLE* t, SNOP_HASHTABLE R);

extern void SNOP_lookup(SNOP_TUPLE* X, SNOP_HASHTABLE R);

extern void SNOP_delete(SNOP_TUPLE* X, SNOP_HASHTABLE R);

extern void SNOP_HASHTABLE_print(const SNOP_HASHTABLE table);

extern void SNOP_HASHTABLE_init(SNOP_HASHTABLE R);

extern void SNOP_generate(SNOP_HASHTABLE R);

#endif
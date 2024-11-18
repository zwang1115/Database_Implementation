#include "SNOP.h"
#include "PSH.h"
#include "PM.h"
#include "PDA.h"
#include "PD.h"

#ifndef QUERY_H
#define QUERY_H

extern void firstQuery(SNOP_HASHTABLE snop_table, PSH_HASHTABLE psh_table);
extern void secondQuery(PDA_HASHTABLE pda_table, PM_HASHTABLE pm_table, SNOP_HASHTABLE snop_table);

#endif
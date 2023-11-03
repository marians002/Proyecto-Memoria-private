#ifndef BNBSTRUCT_H
#define BNBSTRUCT_H
#include "../../utils.h"

typedef struct 
{   
    int pid_proceso;
    int code_size;
    int base;
    // int bounds;
    int* heap;
    int stack;
} bnbProcess;

bnbProcess* init_bnbProcess_array(int proc_amount);

#endif
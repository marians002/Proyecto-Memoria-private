#include <stdio.h>
#include <stdlib.h>
#include "bnbStruct.h"

// Inicializa la estructura bnbProcess

void init_heap(int* heap)
{
    for (int i=0; i<g_heapsize; i++)
        heap[i] = 0;
}

bnbProcess initProcess(int index) {    
    bnbProcess p;

    // Asigna memoria al heap antes de inicializarlo
    p.heap = (int*)malloc(512 * sizeof(int)); 
    init_heap(p.heap); // Llama a init_heap sin asignar el resultado a p.heap
    p.pid_proceso = -1;
    p.base = index * g_heapsize;    
    p.stack = g_heapsize -1;
    
    return p;
}

bnbProcess* init_bnbProcess_array(int proc_amount){
    // Asigna memoria para el array de bnbProcess
    bnbProcess* array_procesos = (bnbProcess*)malloc(proc_amount * sizeof(bnbProcess));

    for (size_t i = 0; i < proc_amount; i++) {
        array_procesos[i] = initProcess(i);
    }

    return array_procesos;
}



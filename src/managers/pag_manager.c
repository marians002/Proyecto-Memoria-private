#include "pag_manager.h"
#include "Structures/pagStruct.h"

#include "stdio.h"


pagStruct* array_procs;
int curr_proc_index = -1; // Indice del proceso actual en el array
int page_size = 256; // tamaño de las páginas
int cant_pages = 4; // cantidad de páginas en la memoria virtual
int page_frame_size = -1; // cantidad de páginas en la memora física
int* page_frame; // indica a que page_frame pertenece en la memoria física

// Inicializa el array de page frame
int* init_page_frame()
{
    // Almacena memoria para el page_frame
    int* pageFrame = (int*)malloc(page_frame_size * sizeof(int));
    
    for (int i = 0; i < page_frame_size; i++) {
        page_frame[i] = -1;
        array_procs[i].proc_pid = -1;  
        array_procs[i].proc_stack = initialize(10000);
        
        // Inicializar las pages
        for (int j = 0; j < 3; j++) {
            array_procs[i].pages[j] = -1;
        }
  }
}

// Busca un proceso en el array de procesos
// Devuelve su posición si lo encuentra, else -1
int find_proc(int pid)
{
    for (int i = 0; i < page_frame_size; i++) 
    {
        if (array_procs[i].proc_pid == pid)
            return i; // Devuelve la posición en el array donde está el proceso
    }
    return -1;
}

// Devuelve el primer índice donde no tengo ningún proceso, else -1
int first_empty()
{
    for (int i = 0; i < page_frame_size; i++) 
    {
        if (array_procs[i].proc_pid == -1)
            return i;
    }
    return -1;
}

// Devuelve el primer frame page vacío, else -1
int first_empty_frame() {
  for (int i = 0; i < page_frame_size; i++) 
  {
    if (page_frame[i] == -1)
      return i;
  }
  return -1;
}

// Esta función se llama cuando se inicializa un caso de prueba
void m_pag_init(int argc, char **argv) {
  // Define el tamaño de los page frame
  page_frame_size = m_size() / page_size;
  // Inicializa el array de procesos
  array_procs = init_pagProcs_array(page_frame_size);
  // Almacena memoria para el array de page frame
  page_frame = init_page_frame();
}

// Reserva un espacio en el heap de tamaño 'size' y establece un puntero al
// inicio del espacio reservado.
int m_pag_malloc(size_t size, ptr_t *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Libera un espacio de memoria dado un puntero.
int m_pag_free(ptr_t ptr) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Agrega un elemento al stack
int m_pag_push(byte val, ptr_t *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Quita un elemento del stack
int m_pag_pop(byte *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Carga el valor en una dirección determinada
int m_pag_load(addr_t addr, byte *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Almacena un valor en una dirección determinada
int m_pag_store(addr_t addr, byte val) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Notifica un cambio de contexto al proceso 'next_pid'
void m_pag_on_ctx_switch(process_t process) {
  // Almacena la posición en el array de procesos donde se encuentra el proceso que entró
  int index = find_proc(process.pid);

  if (index == -1)  // Es un proceso nuevo
  {
    int empty_pos = first_empty();
    
    if (empty_pos != -1)  // Hay un espacio del array de procesos libre
    {
      // Establezco como posición del proceso actual esa que encontré vacía
      curr_proc_index = empty_pos;

      // Establezco el pid del proceso nuevo en el array de procesos
      array_procs[curr_proc_index].proc_pid = process.pid;

      // Posición donde se encontró el primer page_frame vacío
      int empty_frame = first_empty_frame();

      // Si fue distinto de -1 es porque se encontró un page_frame vacío 
      if (empty_frame != -1)
      {
        // Establezco el pid del proceso nuevo en el page frame
        page_frame[empty_frame] = array_procs[curr_proc_index].proc_pid;
        array_procs[curr_proc_index].pages[0] = empty_frame;
        m_set_owner(empty_frame * 256, empty_frame * 256 + 255);

        // Modificar el frame para escribir el código en él
        int fr_code = process.program->size % 256;
        
        for (int i = 0; i <= fr_code; i++) 
        {
          array_procs[curr_proc_index].data[0][i] = 3;
        }
        return;
      }
    }
    else // No hubo espacios libres y no se puede continuar
    {
      fprintf(stderr, "\nError: no quedan espacios libres.\n");
      exit(1);
    }
  }
  // De lo contrario, no es un proceso nuevo y hay que actualizar el proceso actual
  curr_proc_index = index;
}

// Notifica que un proceso ya terminó su ejecución
void m_pag_on_end_process(process_t process) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

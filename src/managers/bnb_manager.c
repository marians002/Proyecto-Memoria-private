#include "bnb_manager.h"
#include "Structures/bnbStruct.h"

#include "stdio.h"

int process_size = 512; // Tamaño que va a ser asignado a cada proceso
bnbProcess* array_procesos;

// Esta función se llama cuando se inicializa un caso de prueba
void m_bnb_init(int argc, char **argv) {
  // Cantidad de procesos que puedo almacenar
  int cant_procesos = m_size() / process_size;
  array_procesos = init_bnbProcess_array(cant_procesos);

  // array_procesos = (bnbProcess*)malloc(cant_procesos * sizeof(bnbProcess));
  // for (size_t i = 0; i < cant; i++) {
  //   context[i].pid = -1;
  //   context[i].base = 0 + h * i;
  //   context[i].p_stack = h - 1;
  //   for (size_t j = 0; j < h; j++) {
  //     context[i].heap[j] = 0;
  //   }    
  // }

}

// Reserva un espacio en el heap de tamaño 'size' y establece un puntero al
// inicio del espacio reservado.
int m_bnb_malloc(size_t size, ptr_t *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Libera un espacio de memoria dado un puntero.
int m_bnb_free(ptr_t ptr) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Agrega un elemento al stack
int m_bnb_push(byte val, ptr_t *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Quita un elemento del stack
int m_bnb_pop(byte *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Carga el valor en una dirección determinada
int m_bnb_load(addr_t addr, byte *out) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Almacena un valor en una dirección determinada
int m_bnb_store(addr_t addr, byte val) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Notifica un cambio de contexto al proceso 'next_pid'
void m_bnb_on_ctx_switch(process_t process) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

// Notifica que un proceso ya terminó su ejecución
void m_bnb_on_end_process(process_t process) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

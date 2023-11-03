#include "bnb_manager.h"
#include "Structures/bnbStruct.h"

#include "stdio.h"

int process_size = 512; // Tamaño que va a ser asignado a cada proceso
bnbProcess* array_procesos; // Array que contiene los procesos
int cant_procesos;  //Define la cantidad de procesos que se pueden almacenar
int current_process_index = -1; // Pid del proceso actual

// Busca un proceso en el array de procesos por su pid
// Devuelve el indice si encuentra el proceso, else -1
int find_proc(int pid) 
{
  for (int i = 0; i < cant_procesos; i++)
  {
    if (array_procesos[i].pid_proceso == pid)
      return i;
  }
  return -1;
}

// Devuelve el primer indice del array de procesos donde no hay ningún proceso guardado.
// Si todo está lleno, devuelve -1.
int first_undef_proc()
{
    for (int i = 0; i < cant_procesos; i++)
    {
        if (array_procesos[i].pid_proceso == -1)
            return i;
    }
    return -1;
}

// Esta función se llama cuando se inicializa un caso de prueba
void m_bnb_init(int argc, char **argv) {
  // Cantidad de procesos que puedo almacenar según el testcase
  cant_procesos = m_size() / process_size;
  array_procesos = init_bnbProcess_array(cant_procesos);
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
  int new_proc_pid = process.pid;
  int c_size = process.program->size;

  int result = find_proc(new_proc_pid);
  if (result != -1) // Encontró el proceso en el array
    current_process_index = result;
  else // El proceso no estaba en el array
  {
    int index = first_undef_proc();
    if (index != -1) // Significa que encontró un espacio libre satisfactoriamente
    {
        current_process_index = index;  // Actualizo el índice del proceso actual
        
        // Inicializo valores en el array de procesos
        array_procesos[index].pid_proceso = new_proc_pid;  
        array_procesos[index].code_size = c_size;
        
        bnbProcess current_proc = array_procesos[current_process_index];
        // Le doy a ese proceso lo que le corresponde en la memoria física
        m_set_owner(current_proc.base, current_proc.base + process_size - 1);
    }
  }
}

// Notifica que un proceso ya terminó su ejecución
void m_bnb_on_end_process(process_t process) {
  fprintf(stderr, "Not Implemented\n");
  exit(1);
}

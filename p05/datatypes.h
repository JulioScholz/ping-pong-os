// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DAINF UTFPR
// Versão 1.0 -- Março de 2015
//
// Estruturas de dados internas do sistema operacional

#ifndef __DATATYPES__
#define __DATATYPES__

#include <ucontext.h>

// Estrutura que define uma tarefa
typedef struct task_t
{
  struct task_t *prev ;
  struct task_t *next ;
  struct task_t *main ;
  struct queue_t **ptr_queue; //referência para  a fila em que a tarefa está inserida
 	char state;
  int t_id ;              //Inteiro para identificação da tarefa
  ucontext_t context;
  int priority_static;
  int priority_dynamic;
  
} task_t ;

// estrutura que define um semáforo
typedef struct
{
  // preencher quando necessário
} semaphore_t ;

// estrutura que define um mutex
typedef struct
{
  // preencher quando necessário
} mutex_t ;

// estrutura que define uma barreira
typedef struct
{
  // preencher quando necessário
} barrier_t ;

// estrutura que define uma fila de mensagens
typedef struct
{
  // preencher quando necessário
} mqueue_t ;

#endif

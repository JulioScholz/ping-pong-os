// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DAINF UTFPR
// Versão 1.0 -- Março de 2015
//
// Estruturas de dados internas do sistema operacional

#ifndef __DATATYPES__
#define __DATATYPES__

#define STACKSIZE 32768	

#define SUSPENDED 's'
#define READY 'r'
#define FINALIZED 'f'
#define IS_RUNNIG 'i'
#define SYSTEM_TASK 0
#define USER_TASK 1
#define QUANTUM 20

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h>

// Estrutura que define uma tarefa
typedef struct task_t
{
  struct task_t *prev ;
  struct task_t *next ;
  struct task_t *main ;
  struct queue_t **ptr_queue; //referência para  a fila em que a tarefa está inserida
 	char state;                 //estado atual da tarefa
  int t_id ;              //Inteiro para identificação da tarefa
  ucontext_t context;     // contexto da tarefa 
  int priority_static;    //prioridade estática da tarefa
  int priority_dynamic;   //prioridade dinâmica da tarefa

  short int t_type; // Tipo de tarefa, se é do sistema(0) ou de usuário(1)
  
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

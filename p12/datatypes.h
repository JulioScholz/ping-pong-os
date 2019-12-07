// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DAINF UTFPR
// Versão 1.0 -- Março de 2015
//
// Estruturas de dados internas do sistema operacional

#ifndef __DATATYPES__
#define __DATATYPES__
#define SLEEP 'd'
#define STACKSIZE 32768	

#define SUSPENDED 's'
#define READY 'r'
#define FINALIZED 'f'
#define IS_RUNNIG 'i'
#define SLEEP 'd'
#define SYSTEM_TASK 0
#define USER_TASK 1
#define QUANTUM 20
#define ON 1
#define OFF 0

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

// Estrutura que define uma tarefa
typedef struct task_t
{
  struct task_t *prev ;
  struct task_t *next ;
  struct task_t *main ;
  struct queue_t **ptr_queue; //referência para  a fila em que a tarefa está inserida
  struct queue_t *ptr_queue_suspended;
 	char state;                 //estado atual da tarefa
  int t_id ;              //Inteiro para identificação da tarefa
  ucontext_t context;     // contexto da tarefa 
  int priority_static;    //prioridade estática da tarefa
  int priority_dynamic;   //prioridade dinâmica da tarefa

  short int t_type; // Tipo de tarefa, se é do sistema(0) ou de usuário(1)

  unsigned int execution;
  unsigned int processor;
  unsigned int act;
  int quantum;

  int suspendedTaskMor;
  int exitCode;
  int isDone;

  int time_sleep;
  
} task_t ;

// estrutura que define um semáforo
typedef struct
{
    int count_sem;
    struct task_t* queue_sem;

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
  //Id da barreira
  unsigned int barrier_id;
  //Tamanho atual da barreira
  unsigned int barrier_size;
  //Tamanho máximo da barreira
  unsigned int barrier_N;
  // Fila de barreiras
  struct task_t* queue_barrier;

 
} barrier_t ;

// estrutura que define uma fila de mensagens
typedef struct
{
  unsigned int max_size;
  unsigned int byte_size;
  unsigned int num_msg;
  int ini;
  int end;
  short int state;
  void* buffer;

  semaphore_t sem_buffer;
  semaphore_t sem_prod;
  semaphore_t sem_cons;
  // preencher quando necessário
} mqueue_t ;

#endif

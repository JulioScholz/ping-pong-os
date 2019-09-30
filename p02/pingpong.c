/*
Alunos: Júlio César Werner Scholz - 2023890
        Juliana Rodrigues Viscenheski - 1508873
Data de inicio: 03/09/2019
Data de término 15/09/2019
*/

#include "pingpong.h"
#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 32768	

task_t  *task_current, task_main;
unsigned long int count_id;  //Como a primera task (main) é 0 a póxima tarefa terá o id 1

// Inicializa o sistema operacional; deve ser chamada no inicio do main()
void pingpong_init () {

    //desativação do buffer da saida padrao (stdout), usado pela função printf
    setvbuf (stdout, 0, _IONBF, 0) ;

    // Tarefa main possui id 0
    task_main.t_id = 0;
    count_id = 1;

    //Inicialização do encademanto das tarefas
    task_main.prev = NULL;
    task_main.next = NULL;

    //Refreência a si mesmo
    task_main.main = &task_main;

    // A tarefa em execução é a main
    task_current = &task_main;

    #ifdef DEBUG
    printf("PingPongOS iniciado com êxito.\n");
    #endif
}

// Cria uma nova tarefa. Retorna um ID> 0 ou erro.
int task_create (task_t *task, void (*start_func)(void *), void *arg){

    char *stack = NULL ;
    task->next = NULL;
    task->prev = NULL;

    // Referência para a tarefa main
    task->main = &task_main;

    // Inicialização do contexto.
    getcontext(&(task->context));

    // Alocação da pilha
    stack = malloc(STACKSIZE);

    if(!stack){
        printf("Error on task_create: criação da stack falhou!\n");
        return -1;
    }

    // Pilha do contexto é atribuída
    task->context.uc_stack.ss_sp = stack;
    task->context.uc_stack.ss_size = STACKSIZE;
    task->context.uc_stack.ss_flags = 0;
    task->context.uc_link = NULL;

    // Cria o contexto com a função
    makecontext (&(task->context), (void*)(*start_func), 1, arg);

    // A nova tarefa recebe o contador, como id
    task->t_id = count_id;
    // O contador é incrementado para que futuras tarefas possam utiliza-lo
    count_id = count_id + 1;

    #ifdef DEBUG
	printf ("task_create: tarefa %d criada com sucesso\n", task->t_id);
    #endif
    
    return ((int)task->t_id);
}

// alterna a execução para a tarefa indicada
int task_switch (task_t *task){

    task_t *task_previous = NULL;

    if(task == NULL){
        printf("Error on task_switch: A tarefa é nula! \n");
        return -1;
    }
    // ponteiro auxiliar que indica a tarefa anterior.
    task_previous = task_current;
    // a tarefa corrente passa a ser a nova tarefa recebida.
    task_current = task;

    #ifdef DEBUG
    printf ("task_switch: trocando contexto %d -> %d\n", task_previous->t_id, task->t_id) ;
    #endif 
    // troca de contextos
    if (swapcontext (&(task_previous->context), &(task->context)) < 0) {
        printf ("Error on task_switch: Troca de Contexto falhou! \n");
        return -1;
    }
    return 0;
}

// Termina a tarefa corrente, indicando um valor de status encerramento
void task_exit (int exitCode) {
    #ifdef DEBUG
    printf ("task_exit: tarefa %d sendo encerrada\n", task_current->t_id) ;
    #endif  
	task_switch(&task_main);
}

// retorna o identificador da tarefa corrente (main é 0)
int task_id (){
    #ifdef DEBUG
    printf ("task_id: ID da tarefa %d\n", task_current->t_id) ;
    #endif 
    return (task_current->t_id);
}
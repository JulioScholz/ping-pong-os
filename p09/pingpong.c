/*
Alunos: Júlio César Werner Scholz - 2023890
        Juliana Rodrigues Viscenheski - 1508873
Data de inicio: 03/09/2019
Data de término 26/09/2019
p09 - início 10/11/2019
*/
#include "pingpong.h"

task_t *task_current, *task_main, *task_dispacther;
task_t *queue_ready = NULL;
task_t *queue_sleep = NULL;
unsigned long int count_id;  //Como a primera task (main) é 0 a póxima tarefa terá o id 1
struct sigaction action ; // estrutura que define um tratador de sinal (deve ser global ou static)
struct itimerval timer; // estrutura de inicialização to timer
int quantum;
unsigned int delta = 0;
unsigned int timeInit = 0;
unsigned int timeLast = 0;
unsigned int count_task = 0;

int exitCodeReturned;

void dispatcher_body(void* arg);
task_t* scheduler();
void signal_handler(int singnum); // Função que trata os sinais recebidos

// Inicializa o sistema operacional; deve ser chamada no inicio do main()
void pingpong_init () {

    //desativação do buffer da saida padrao (stdout), usado pela função printf
    setvbuf (stdout, 0, _IONBF, 0) ;
    count_id = 0;
    task_main = malloc(sizeof(task_t));
    task_create(task_main, 0, "main"); //alt: qual seria a equivalência do dispatcher_body?
    task_main->t_type = USER_TASK;

    // criação da tarefa dispatcher
    task_dispacther = malloc(sizeof(task_t));
    task_create(task_dispacther,(void*)(dispatcher_body), "dispatcher");
    count_task--;// O dispatcher nao pode ser contado como tarefa ativa pois se trata de uma tarefa de sistema.
    task_dispacther->t_type = SYSTEM_TASK;

    // A tarefa em execução é a main
    task_current = task_main;

    //Inicialização de timer e sinais e demais tratamentos para os mesmos
    #ifdef DEBUG
    printf("Setando timers e sinais\n");
    #endif
    action.sa_handler = signal_handler;
    sigemptyset (&action.sa_mask) ;
    action.sa_flags = 0 ;
    if (sigaction (SIGALRM, &action, 0) < 0)
    {
        printf ("Erro em pingpong_init(): Erro em sigaction\n ") ;
        exit (1) ;
    }

    // ajusta valores do temporizador
    timer.it_value.tv_usec = 100 ;      // primeiro disparo, em micro-segundos
    timer.it_value.tv_sec  = 0 ;      // primeiro disparo, em segundos
    timer.it_interval.tv_usec = 1000 ;   // disparos subsequentes, em micro-segundos
    timer.it_interval.tv_sec  = 0 ;   // disparos subsequentes, em segundos

    // arma o temporizador ITIMER_REAL (vide man setitimer)
    if (setitimer (ITIMER_REAL, &timer, 0) < 0)
    {
        printf ("Erro em pingpong_init(): Erro em setitimer \n") ;
        exit (1) ;
    }


    #ifdef DEBUG
    printf("PingPongOS iniciado com êxito.\n");
    #endif

    //task_switch(task_dispacther);
    task_yield();
}

// Cria uma nova tarefa. Retorna um ID> 0 ou erro.
int task_create (task_t *task, void (*start_func)(void *), void *arg){

    char *stack = NULL;

    task->next = NULL;
    task->prev = NULL;
    //task->quantum = QUANTUM;

    task->isDone = 0;

    // Referência para a tarefa main
    task->main = task_main;

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
   // printf("%ld count \n", count_id);
    task->t_id = count_id;

    task->execution = systime();
    task->act = 0;
    task->processor = 0;

    // O contador é incrementado para que futuras tarefas possam utiliza-lo
    count_id = count_id + 1;

    //A criaçao da tarefa terminou, seu estado passa a ser READY ('r')
    task->state = READY;

    // Seta a prioridade estática e dinâmica para 0
    task->priority_static = 0;
    task->priority_dynamic = 0;
    task->t_type = USER_TASK;
    task->ptr_queue_suspended =NULL;
    count_task++;

    if(task->t_id > 1){
        task->t_type = USER_TASK;
        queue_append((queue_t**)(&queue_ready),(queue_t*)(task));
        task->ptr_queue = (queue_t**)(&queue_ready);

    #ifdef DEBUG
    printf("task_create: Task %d foi adicionada a fila de prontos\n", task->t_id);
    #endif
    }

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
    //  task_previous.state
    // a tarefa corrente passa a ser a nova tarefa recebida.
    task_current = task;

    #ifdef DEBUG
    printf ("task_switch: trocando contexto %d -> %d\n", task_previous->t_id, task->t_id) ;
    #endif
    // troca de contextos
    if (swapcontext (&(task_previous->context), &(task_current->context)) < 0) {
        printf ("Error on task_switch: Troca de Contexto falhou! \n");
        return -1;
    }
    return 0;
}

// Termina a tarefa corrente, indicando um valor de status encerramento
void task_exit (int exitCode) {
  
	task_current->state = FINALIZED;
	/* Tarefa sendo encerrada ... */
	/* Mostrar dados finais da tarefa */
    task_current->execution = systime() - task_current->execution;
    printf ("Task %d exit: execution time %d ms, processor time %d ms, %d activations\n", task_current->t_id,
            task_current->execution, task_current->processor, task_current->act);


	#ifdef DEBUG
	printf("task_exit: tarefa %d sendo encerrada\n", task_current->t_id);
	#endif

	/* Desbloquear as tarefas que deram join nessa */
	if (task_current->ptr_queue_suspended)
	{
		while (task_current->ptr_queue_suspended)
		{
            exitCodeReturned = exitCode;
            task_current->exitCode = exitCode;
            task_current->isDone = 1;
			task_resume(task_current->ptr_queue_suspended);
		}
	}

	/* Finalizar o código se for o dispatcher (última task e terminar) */
	if (task_current == task_dispacther)
	{
		#ifdef DEBUG
		printf("task_exit: Dispatcher finalizado\n");
		#endif
		exit(0);
	}
	/* Senao temos que retornar para o dispatcher mesmo */
	else
	{
		#ifdef DEBUG
		printf("task_exit: voltando para o dispatcher\n");
		#endif
		/*
		 * Flag para indicar ao dispatcher que a tarefa foi encerrada
		 * para limpeza de variáveis dessa tarefa.
		 */
        count_task--;
		
		task_switch(task_dispacther);
	}

}

// retorna o identificador da tarefa corrente (main é 0)
int task_id (){
    #ifdef DEBUG
    printf ("task_id: ID da tarefa %d\n", task_current->t_id) ;
    #endif
    return (task_current->t_id);
}

// em função da implementação do dia 23/09, agora o algoritmo está mais para um PRIOp
task_t *scheduler(){
    
    task_t *task_aux = NULL;

    // Se a fila estiver vazia
    if (queue_ready == NULL)
        return NULL;

        // Se somente um elemento está contido na fila de prontas
        // Este único elemento é escolhido;
    else if ( queue_ready == queue_ready->next )
    {
        task_aux = queue_ready;
    }

        //se a fila conter mais de um elemento
    else{
        // ponteiro para a tarefa que será escolhida
        task_t* priority_task = queue_ready;
        task_aux = queue_ready;
        // inteiro auxiliar quer armazzenara o valor da prioridade dinamica da tarefa a ser comparada
        int aux_prio_d;

        do{
            //Envelhicento de tarefas, respeitando o range de prioridade.
            aux_prio_d = task_aux->priority_dynamic;
            // Critério: a tarefa prioritaria sempre será uma tarefa comprioridade menor ou igual a atual
            if( priority_task->priority_dynamic >  aux_prio_d ){

                //Como a prioridade dinâica da tarefa seguinte é menor, ela é escolhida
                priority_task = task_aux;
            }

            //Proxima tarefa a ser comparada
            task_aux = task_aux->next;

        }while(task_aux != queue_ready);

        task_aux = queue_ready;
        do{
            if (task_aux->priority_dynamic > -20)
                task_aux->priority_dynamic--;
            task_aux = task_aux->next;

        }while(task_aux != queue_ready);



        task_aux = priority_task;
    }
    #ifdef DEBUG
    printf("scheduler: Task %d foi escolhida pelo scheduler\n", task_aux->t_id);
    #endif

    //como a tarefa foi escolhida sua pripridade dinâmica é resetada;
    task_aux->priority_dynamic =  task_aux->priority_static;

    return task_aux;
}

void dispatcher_body (void *arg) // dispatcher é uma tarefa
{
    int cont_sleep_tasks = 0;
    // Enquanto houverem tarefas prontas para serem executadas o loop continua
    while (count_task > 0)
    {
        cont_sleep_tasks = (int)queue_size((queue_t*)queue_sleep);
        task_t *task_aux = queue_sleep;
        // percorre a fila de tarefas adormecidas 
        while(cont_sleep_tasks > 0  && queue_sleep  != NULL){
            // e acorda todas as tarefas que já podem ser acordadas
            if (systime() >= (unsigned int)task_aux->time_sleep){ 

                #ifdef DEBUG
                printf("dispatcher_body: Tarefa %d sendo acordada\n",task_aux->t_id);
                #endif

                task_resume(task_aux);

                #ifdef DEBUG
                printf("dispatcher_body: Tarefa %d acordou\n",task_aux->t_id);
                #endif

            }
            else{
                task_aux = task_aux->next;
            }
            cont_sleep_tasks = cont_sleep_tasks - 1;  
        }
    
        task_t *task_next;
        task_next = NULL;
        // a funçao scheduler decide qual a proxima tarefa a ser executada
        task_next = scheduler() ; // scheduler retorna a proxima tarefa

        if (task_next != NULL){
            //Numero de ativações incrementado da tarefa dispatcher
            task_dispacther->act++;
            // contabiliza o início da próxima  tarefa
            timeLast = timeInit;
            // como o delta é o nosso relógio corrido, o início da tarefa será o tempo atual do delta
            timeInit = systime();

            // Remoção da proxima tarefa a ser executa da fila de prontos, por meio do casting para queue_t
            queue_remove((queue_t**)&queue_ready, (queue_t*)task_next);
            #ifdef DEBUG
            printf("dispatcher_body: Task %d foi removida da fila de prontos\n", task_next->t_id);
            #endif
            task_next->ptr_queue = NULL;
            //O quantum é resetado para o valor padrão do sistema:
            quantum = QUANTUM;
            // aumenta o número de ativações da tarefa, uma vez que o dispatcher precisou ativá-la
            task_next->act++;
            // a tarafa next é lançada
            task_switch (task_next) ; // transfere controle para a tarefa "next"
            // ... // ações após retornar da tarefa "next", se houverem
        }
    }
    #ifdef DEBUG
    printf("dispatcher_body: Dispatcher sendo encerrado!\n");
    #endif
    task_exit(0) ; // encerra a tarefa dispatcher
}

// libera o processador para a próxima tarefa, retornando à fila de tarefas
// prontas ("ready queue")
void task_yield () {

    if (task_current->t_id != 1) {
        queue_append((queue_t**)&queue_ready, (queue_t*)(task_current));
        task_current->ptr_queue =(queue_t**) (&queue_ready);
       // task_current->state = READY;
        #ifdef DEBUG
        printf("task_yield: Task %d foi adicionada a fila de prontos\n", task_current->t_id);
        #endif
    }
    // Dispatcher assume o controle
    task_switch(task_dispacther);
}

void signal_handler(int singnum) {

    //Se a tarefa atual for uma tarefa de usário ela poderá ser “preemptada” caso necessário
    // então a cada chama do tratador seu quantum diminui

    // relógio aumenta
    delta++;
    if (task_current->t_type == USER_TASK) {
        if (quantum < 1) {
            #ifdef DEBUG
            printf("signal_handler: Tarefa chegou ao final do quantum: %d\n", task_current->t_id);
            #endif
            task_current->act++;
            // o tempo de processador será o tempo total (delta corrido) menos o momento no qual a última tarefa foi finalizada
            task_current->processor += systime() - timeLast;
            task_yield();
        } 
        else {
            quantum--;
        }
        return;
    }

}

// suspende uma tarefa, retirando-a de sua fila atual, adicionando-a à fila
// queue e mudando seu estado para "suspensa"; usa a tarefa atual se task==NULL
void task_suspend(task_t *task, task_t **queue)
{
	#ifdef DEBUG
	printf ("task_suspend: inicio\n");
	#endif


	if (queue == NULL){
        #ifdef DEBUG
	    printf ("task_suspend: queue passada como parametro é nula!\n");
	    #endif
		return;
    }
    else if(task == NULL){
		task = task_current;
    }

	#ifdef DEBUG
	printf ("task_suspend: tarefa %d sendo suspensa\n", task->t_id);
	#endif
	
	queue_append((queue_t**)queue, (queue_t*)task);
	task->ptr_queue =(queue_t**) queue;
    if(task->state != SLEEP){
	    task->state = SUSPENDED;
    }

	task_switch(task_dispacther);
}

// acorda uma tarefa, retirando-a de sua fila suspended, adicionando-a à fila de
// tarefas prontas ("ready queue") e mudando seu estado para "pronta"
void task_resume (task_t *task){
    if(task->state == FINALIZED){
        return;
    }
    if(task->ptr_queue  != NULL){
        task = (task_t*)queue_remove((queue_t**)task->ptr_queue,(queue_t*)(task));
    }
    #ifdef DEBUG
    printf("task_resume: tarefa %d sendo resumida\n", task->t_id);
    #endif
    task->state = READY;
    queue_append((queue_t**)&queue_ready,(queue_t*)(task));
    task->ptr_queue =(queue_t**) &queue_ready;
}

// recolhe a prioridade estática da tarefa task
int task_getprio (task_t *task) {

    if (task != NULL)
        return task->priority_static;
    else
        return task_current->priority_static;
}

// seta a prioridade
void task_setprio (task_t *task, int prio){
    if (prio < -20 || prio > 20)
        printf("Error on task_setprio: Impossível setar prioridade fora do range\n");

    if (task != NULL){
        task->priority_dynamic= prio;
        task->priority_static = prio;
    }
    else{
        task_current->priority_dynamic = prio;
        task_current->priority_static = prio;
    }
}

// retorna o relógio atual (em milisegundos)
unsigned int systime (){
    return delta;
}

int task_join (task_t *task) {
	if (task == NULL || task_current == NULL)
	{
        #ifdef DEBUG
	    printf ("task_join: nao foi possivel dar join alguma task é nula\n");
	    #endif
		return -1;
	}
    if( task->state == FINALIZED){
        return task->exitCode;
    }
    #ifdef DEBUG
	printf ("task_join: tarefa %d dando join na tarefa %d\n", task_current->t_id, task->t_id);
	#endif
	 // Tarefa perde o processador
	 // E é colocada na fila de suspensas da tarefa passada
	 // O dispatcher assume o controle na chamada de task suspend
     // E essa tarefa aguarda receber o processamento novamente
	#ifdef DEBUG
	printf ("task_join: A suspensão irá ocorrer \n");
	#endif
	task_suspend(task_current, &(task->ptr_queue_suspended));

	#ifdef DEBUG
	printf ("task_join: voltando da suspensão (exit_code = %d)\n", task_current->exitCode);
	#endif

	return task_current->exitCode;

}

void task_sleep (int t){
    //o tempo de dormência estipulado deve ser maior que 0
    if (t >= 1) {
        task_current->state = SLEEP;	
        #ifdef DEBUG
        printf ("task_sleep: Tarefa %d irá dormir por %d seg\n",task_current->t_id,t);
        #endif
        task_current->time_sleep = (int)(systime() + t*1000) ;   // tempo de dormência definido
        // adiciona a fila de tarefas adormecidas
        task_suspend(task_current,&queue_sleep);
    }
    return;
}

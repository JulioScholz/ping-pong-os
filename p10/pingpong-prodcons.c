#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "pingpong.h"

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

unsigned int item;
unsigned int buffer[5];
task_t prod1, prod2, prod3, cons1, cons2;
semaphore_t s_vaga,s_buffer,s_item;

int has_space(){
    for(int i =0; i < 5;i++){
        if(buffer[i] == -1){
            return i;
        }
    }
    return -1;
}


void produtor(void *arg)
{
    int pos;
    for(;;)
    {
        task_sleep (1);
        item = rand()%100;
        sem_down (&s_vaga);
        sem_down (&s_buffer);
        pos = has_space();
        if(pos != -1){
            buffer[pos] = item; 
            printf("%s produziu %d\n", (char*)arg, item);
        }
        sem_up (&s_buffer);
        sem_up(&s_item);
    }

}

void consumidor(void *arg)
{
    for(;;)
    {
        sem_down (&s_item);
        sem_down (&s_buffer);
        if(buffer[0] != -1){
            printf("							%s consumiu %d\n", (char*)arg, buffer[0]);
            for(int i = 0; i < 4;i++){
             buffer[i] = buffer[i+1];
            }
             buffer[4] = -1;
        }
        sem_up (&s_buffer);
        sem_up (&s_vaga);
        task_sleep (1);
    }
}


int main()
{
    srand(time(NULL));
    //inicializaçãod buffer
    for(int i = 0; i < 5;i++){
        buffer[i] = -1;
    }

	printf("Main INICIO\n");
	pingpong_init();

	sem_create(&s_vaga, 5);
	sem_create(&s_buffer, 1);
	sem_create(&s_item, 0);

    

	task_create(&prod1, produtor, "p1");
	task_create(&prod2, produtor, "p2");
	task_create(&prod3, produtor, "p3");
	task_create(&cons1, consumidor, "c1");
	task_create(&cons2, consumidor, "c2");

	printf("Main FIM\n");
	task_exit(0);

    return 0;
}

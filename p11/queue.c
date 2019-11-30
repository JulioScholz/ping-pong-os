/*
Alunos: Júlio César Werner Scholz - 2023890
        Juliana Rodrigues Viscenheski - 1508873
Data de inicio: 31/08/2019
Data de término 01/09/2019
*/

#include "queue.h"
#include <stdio.h>

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila

void queue_append (queue_t **queue, queue_t *elem) {

    //printf("entrou no append\n ");

    if (queue == NULL){
        printf("Error on queue_append: Fila nao existe!\n");
        return;
    }
    if(elem == NULL){
        printf("Error on queue_append: Elemento nao existe! \n");
        return;
    }
    if (elem->prev !=NULL){
        printf("Error on queue_append: O elemento possui ligacao em outra fila! \n");
        return;
    }

    //inserção de um elemento em uma fila circular vazia
    if(*queue == NULL){
        *queue = elem;
        elem->next = elem;
        elem->prev =elem;
    }
    //se a fila nao está vazia insere o elemento ao final da fila existente.
    else{
        //queue_t *ultimo_elemento = NULL;
        //ultimo_elemento = (*queue)->prev;
        /*
        queue_t *auxiliar = NULL;
        auxiliar = (*queue)->next;
        while(auxiliar != elem){
            if(auxiliar == (*queue)){ //se chegou ao inicio da fila
                elem->prev = auxiliar->prev;
                auxiliar->prev->next = elem;
                elem->next = auxiliar;
                auxiliar->prev = elem;

            }
            auxiliar = auxiliar->next;
        }
         */
        //printf("fila nao ta vazia \n");
        elem->prev = (*queue)->prev; // o novo ultimo elemento tem como anterior o antigo ultimo elemento
        (*queue)->prev->next = elem; // o antigo ultimo elemento recebe como proximo o novo ultimo elemento
        elem->next = *queue;    //fila circular, ou seja o proximo ao ultimo elemento é o primeiro elemento
        (*queue)->prev = elem;  //o mesmo aqui, o anterior ao primeiro elemento é o novo ultimo elemento
    }
}

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove (queue_t **queue, queue_t *elem) {
    if (queue == NULL){
        printf("Error on queue_remove: Fila nao existe!\n");
        return NULL;
    }
    if(*queue == NULL){
        printf("Error on queue_remove: Fila esta vazia!\n");
        return NULL;
    }
    if(elem == NULL){
        printf("Error on queue_remove: Elemento nao existe! \n");
        return NULL;
    }
    
    queue_t *auxiliar = NULL;
    auxiliar = (*queue)->next;

    while(auxiliar != elem){ 

        if(auxiliar == (*queue)){ //se chegou ao inicio da fila é poque o elemento nao foi encontrado
            printf("Error on queue_remove: O elemento não se encontra na fila!\n");
            auxiliar = NULL;
            return NULL;
        }
        auxiliar = auxiliar->next;
    }

    auxiliar = NULL;

    //necessário verificar se a fila contem somente um elemento
    //caso positivo é necessário um tratamento diferete

    if((*queue) == elem && (*queue)->prev == elem && (*queue)->next == elem){
        elem->prev = NULL;
        elem->next = NULL;
        (*queue)   = NULL;
        return elem;
    }

    
    //reajuste da fila, caso o elemento a ser removido seja o primeiro na fila 
    if ((*queue) == elem) {
        (*queue) = elem->next;
    }

    // "juntando" a fila, que será repartida com a remoção de um elemento
    (elem->prev)->next = elem->next;
    (elem->next)->prev = elem->prev;

    //desligamento do elemento da fila
    elem->next = NULL;
    elem->prev = NULL;

    return elem;
}

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size (queue_t *queue) {

    if( queue == NULL){
        return 0;
    }

    int size = 1;
    queue_t* auxiliar = NULL;
    auxiliar = queue->next;

    while (auxiliar != queue){
        size = size + 1;
        auxiliar = auxiliar->next;
    }
    auxiliar = NULL;

    return size;
}

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
    printf("%s [",name);
    
    if(queue == NULL){
        printf("]\n");
        return;
    }
    queue_t *auxiliar = NULL;
    auxiliar = queue;

    while(auxiliar != queue->prev){
        print_elem(auxiliar);
        printf(" ");
        auxiliar = auxiliar->next;
    }
    print_elem(auxiliar);

    printf("]\n");

    return;
}
/**************************************
 
	Uma pilha projetada para ser uma fila de
	prioridade para o algoritmo
	Dijkstra.

	A pilha armazena índices para o
	matriz de nós do gráfico. A prioridade é
    a distância até o nó de origem.

***************************************/

#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>
#include "graph.h"

/*
	Uma função que compara nós de um gráfico e me diz qual está mais próximo
	do nó de origem. Os inteiros são índices para a matriz de nós
	do gráfico do primeiro parâmetro.
*/
typedef int (heap_compare)(graph*, unsigned int, unsigned int);

#define HEAP_LEFT(nodo) ((nodo)+(nodo)+1)
#define HEAP_RIGHT(nodo) ((nodo)+(nodo)+2)
#define HEAP_PARENT(nodo) (((nodo)-1)>>1)

typedef struct {
    unsigned int* nodes;
    unsigned int space;
    unsigned int count;
    heap_compare* compare;
	graph* g; /* Esta pilha contém índices na matriz de nós do gráfico */
} heap; 

/*
	Coloca todos os elementos do gráfico na pilha, em ordem de distância
	à origem, segundo Dijkstra.
	
	O(|V| log|V|)
*/	

heap* criaPilha(heap_compare*, graph*);

void inserePilha(heap*, const unsigned int);

/*
	Encontra o item com a maior prioridade, ou seja, o menor índice.
	O(1)
*/

unsigned int heap_find_min(const heap*);

/*
	Procura o elemento com a prioridade mais alta, ou seja, o índice mais baixo e
	sai da pilha, reestruturando o monte.
	O(log n)
*/

unsigned int heap_delete_min(heap*);

/*
	Imprime a pilha no console.
*/
void heap_dump(const heap*, const unsigned int);

/*
	Libera a memoria de uma pilha.
*/
void heap_destroy(heap*);

bool heap_is_empty(const heap*);

/*
	Reestrutura a pilha após ter alterado uma prioridade, indo para
prioridade mais alta (índice mais baixo).
O parâmetro é o índice da matriz interna da pilha onde é desejado
corrigir possíveis violações de propriedade.
	
*/
void heap_heapify_up(heap*, unsigned int);
										
#endif HEAP_H
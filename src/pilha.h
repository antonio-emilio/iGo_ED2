/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/


#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "grafo.h"

/*
	Uma função que compara nós de um gráfico e me diz qual está mais próximo
	do nó de origem. Os inteiros são índices para a matriz de nós
	do gráfico do primeiro parâmetro.
*/
typedef int (comparaPilha)(grafo*, unsigned int, unsigned int);

#define PILHA_ESQUERDA(nodo) ((nodo)+(nodo)+1)
#define PILHA_DIREITA(nodo) ((nodo)+(nodo)+2)
#define PILHA_PAI(nodo) (((nodo)-1)>>1)

typedef struct {
    unsigned int* nos;
    unsigned int espaco;
    unsigned int contador;
    comparaPilha* comparar;
	grafo* g; /* Esta pilha contém índices na matriz de nós do gráfico */
} pilha; 

/*
	Coloca todos os elementos do gráfico na pilha, em ordem de distância
	à origem, segundo Dijkstra.
	
	O(|V| log|V|)
*/	

pilha* criaPilha(comparaPilha*, grafo*);

void inserePilha(pilha*, const unsigned int);

/*
	Encontra o item com a maior prioridade, ou seja, o menor índice.
	O(1)
*/

unsigned int encontraMinPilha(const pilha*);

/*
	Procura o elemento com a prioridade mais alta, ou seja, o índice mais baixo e
	sai da pilha, reestruturando o monte.
	O(log n)
*/

unsigned int deletaMinPilha(pilha*);

/*
	Imprime a pilha no console.
*/
void imprimePilha(const pilha*, const unsigned int);

/*
	Libera a memoria de uma pilha.
*/
void destroiPilha(pilha*);

bool pilhaVazia(const pilha*);

/*
	Reestrutura a pilha após ter alterado uma prioridade, indo para
prioridade mais alta (índice mais baixo).
O parâmetro é o índice da matriz interna da pilha onde é desejado
corrigir possíveis violações de propriedade.
	
*/
void aumentaPrioridade(pilha*, unsigned int);
										
#endif PILHA_H
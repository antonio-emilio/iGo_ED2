/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "grafo.h"

/*
	Implementação do algoritmo de Dijkstra para uma fonte. O inteiro passado é o indice na matriz de nós do gráfico onde está a fonte.
*/

void dijkstra(grafo*, unsigned int);
void dijkstra2(grafo*, unsigned int);

#endif
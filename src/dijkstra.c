/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include "dijkstra.h"
#include "pilha.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double* distances;

int comparar(grafo* g, unsigned int i, unsigned int j) {
    if(g->nos[i].distancia == g->nos[j].distancia) { return 0; }
    if(g->nos[i].distancia > g->nos[j].distancia) { return 1; }
    return -1;
}

void dijkstra(grafo* g, unsigned int origem) {

	if(origem == -1){
		printf("\nLocalizacao nao reconhecida.\n");
		return;
	}

	unsigned int u, v, contadorVertice;
	no *n, *d;
	vertice *e;
	pilha *Q;

	g->nos[origem].distancia = 0;
	Q = criaPilha(comparar, g);

	while(!pilhaVazia(Q)) {
		
		u = deletaMinPilha(Q);
		n = &g->nos[u];
		contadorVertice = n->contadorVertice;
		for(v = 0; v < contadorVertice; v++) {	
			
			e = &n->Vertices[v];	
			d = &g->nos[e->destino];
			if(d->distancia > n->distancia + e->pesoVertice) {		
				d->distancia = n->distancia + e->pesoVertice;
				/* 
					Atualiza a distância. 
				*/
				d->anterior = u;
				/* 
					Atualiza a fila de prioridade (o vértice só pode aumentar em prioridade).
				*/
				aumentaPrioridade(Q, d->indicePilha);			
			}
		}
	}
	destroiPilha(Q);
}


void dijkstra2(grafo* g, unsigned int origem) {

	if(origem == -1){
		printf("\nLocalizacao nao reconhecida.\n");
		return;
	}

	unsigned int u, v, contadorVertice;
	no *n2, *d2;
	vertice *e2;
	pilha *Q2;

	g->nos[origem].distancia = 0;
	Q2 = criaPilha(comparar, g);

	while(!pilhaVazia(Q2)) {
		
		u = deletaMinPilha(Q2);
		n2 = &g->nos[u];
		contadorVertice = n2->contadorVertice;
		for(v = 0; v < contadorVertice; v++) {	
			
			e2 = &n2->Vertices[v];	
			d2 = &g->nos[e2->destino];
			if(d2->distancia > n2->distancia + e2->pesoVertice) {		
				d2->distancia = n2->distancia + e2->pesoVertice;
				/* 
					Atualiza a distância. 
				*/
				d2->anterior = u;
				/* 
					Atualiza a fila de prioridade (o vértice só pode aumentar em prioridade).
				*/
				aumentaPrioridade(Q2, d2->indicePilha);			
			}
		}
	}
	destroiPilha(Q2);
}
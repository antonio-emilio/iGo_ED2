/****************************
 
 * 1) Tipos de datos de grafo.
 * 2) API publica de grafos.

****************************/
#ifndef GRAPH_H
#define GRAPH_H

struct node;

/* 
	Um vertice direcional tem uma fonte, direcao e um peso.
*/
typedef struct {
    unsigned int source;
    unsigned int destination;
    double weight;
} edge;
 

/* 	
	Um nó tem vértices adjacentes. verticeCount é a quantidade de vertices adjanteces.
	VerticeSpace é o espaço alocado para os vértices.
*/

typedef struct node {
    edge* edges;
    unsigned int edge_count;
    unsigned int edge_space;
   	char* value;

/* 
	Distancia estimada pelo algoritimo de Dijkstra.
*/
    double distance;
/* 
	Utilizado para manter a prioridade do algoritmo.
*/ 
    int heap_index;
/* 
	O nó anterior no caminho mais curto, de acordo com o algoritmo de Dijkstra. É um índice para matriz de nós do gráfico.
*/ 
	int previous;
} node; 


typedef struct {
    node* nodes;
    unsigned int node_count;
    unsigned int node_space;
} graph;

/* 
	Cria um grafo.
*/

graph* graph_make();

/* 
	Inclui um nó ao grafo. 
*/
void graph_add_node(graph*, char*);
/* 
	Inclui um vértice ao grafo.
*/
void graph_add_edge(graph*, unsigned int, unsigned int, double);

/*
	Destroi um grafo e libera sua memoria.
*/

void graph_destroy(graph*);

/*
	Imprime o grafo no console.
*/
void graph_dump(graph*, int);

#endif // GRAPH_H
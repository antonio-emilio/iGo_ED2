/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/


#ifndef GRAFO_H
#define GRAFO_H

struct no;

/* 
	Um vertice direcional tem uma fonte, direcao e um peso.
*/
typedef struct {
    unsigned int origem;
    unsigned int destino;
    double pesoVertice;
} vertice;
 

/* 	
	Um nó tem vértices adjacentes. verticeCount é a quantidade de vertices adjanteces.
	VerticeSpace é o espaço alocado para os vértices.
*/

typedef struct no {
    vertice* Vertices;
    unsigned int contadorVertice;
    unsigned int espacoVertice;
   	char* nome;

/* 
	Distancia estimada pelo algoritimo de Dijkstra.
*/
    double distancia;
/* 
	Utilizado para manter a prioridade do algoritmo.
*/ 
    int indicePilha;
/* 
	O nó anterior no caminho mais curto, de acordo com o algoritmo de Dijkstra. É um índice para matriz de nós do gráfico.
*/ 
	int anterior;
} no; 


typedef struct {
    no* nos;
    unsigned int contadorNos;
    unsigned int espacoNo;
} grafo;

/* 
	Cria um grafo.
*/

grafo* criarGrafo();

/* 
	Inclui um nó ao grafo. 
*/
void adicionarNo(grafo*, char*);
/* 
	Inclui um vértice ao grafo.
*/
void adicionaVertice(grafo*, unsigned int, unsigned int, double);

/*
	Destroi um grafo e libera sua memoria.
*/

void liberaGrafo(grafo*);

/*
	Imprime o grafo no console.
*/
int mostraCaminhos(grafo *g, int destinoMarcado, int modoDepuracao, int origemMarcada);

#endif // GRAFO_H
/*
Atividade Extra de Grafos : usuario SIMPLES;
 	
 	Este programa trata um mapa simples de usuario com um mapa de n por m posições.
 
 	As posições do mapa são tratadas como vértices de um grafo enquanto que as ligações
 entre essas posições(que permitem o jogador, ou o inimigo, andar) são representadas
 como as arestas.
	Desse modo, são sorteadas posições aleatórias para o usuario e o destino e, em sequência
 um algoritmo de IA wavefront é utilizado para que o usuario escolha o melhor(ou menor) caminho
 possível até que chegue no destino(que se movimenta aleatoriamente).
*/

#include <stdlib.h>
#include "grafo.c"
#include "grafo.h"
#include "fila.c"
#include "fila.h"
#include <stdio.h>
#include <time.h>
#include "prototypes.h"

/*
Estrutura posicao criada para representar uma posição de um elemento no mapa do mapa.
Note que possui duas coordenadas: x e y, como representado comumente em um game;
*/
typedef struct posicao{
	int x;
	int y;
	int trafego;
}Posicao;


/*Declaração de funções*/
void imprimir_mapa(Posicao usuario, Posicao destino, int n, int m);
void destino_caminha(Posicao *destino, int n, int m);


int main(){


	/*     for (;;)
    {
        defineCor('g');
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~iWay~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("                   * Caminhos inteligentes. *\n                    ");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("|Digite um numero correspondente no menu:                         |\n");
        printf("|1. Visualizar mapa;                                              |\n");
        printf("|2. Definir destino;                                              |\n");
        printf("|3. Verificar transito atual;                                     |\n");
        printf("|4. Visualizar ultimos destinos;                                  |\n");
        printf("|5. Sair;                                                         |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        defineCor('n');
        scanf("%d",&escolha);

        switch(escolha){
            case 1: 
            break;

            case 2:
            break;

            case 3: 
            break;

            case 4: 
            break;

            case 5: 
            return 0;
            break;

        }

    }*/

	int n, m; //lados do tabuleiro m x n
	printf("Digite as dimensões do mapa: ");
	scanf("%d%d", &n, &m);
	getchar();
	int v = n * m; // v -> número de vértices
	int erro = 0, direcionado = 0;
	int aresta = 0; // indica que o valor inicial que representa a existência de uma aresta é 0.
	
	//grafo de n*m vertices não direcionado
	Grafo *G = criar_grafo(&v, &erro, &direcionado);

	/*Insere todas as arestas que ligam os vértices de acordo com o mapa do mapa*/
	for(int i=0; i<v; i++){
		int esquerda = i-1, direita = i+1, cima = i-m, baixo = i+m;
		//Insere conferindo se não está na borda do mapa para cada situação:
		if(i % m != 0) inserir_aresta(G, &i, &(esquerda), &aresta, &erro); //insere a esquerda
		if(i % m != (m-1)) inserir_aresta(G, &i, &(direita), &aresta, &erro); //insere a direita
		if(i >= m) inserir_aresta(G, &i, &(cima), &aresta, &erro); //insere em cima
		if(i < (m * n - n)) inserir_aresta(G, &i, &(baixo), &aresta, &erro); //insere em baixo
	}

	//escolhe um vertice para o destino e um para o usuario de forma aleatória:
	srand(time(NULL));
	Posicao usuario, destino;
	usuario.x = rand() % m;
	usuario.y = rand() % n;
	destino.x = rand() % m;
	destino.y = rand() % n;

	int aux = 1;
	int chegou = 0;
	if(usuario.x == destino.x && usuario.y == destino.y) chegou = 1;

	imprimir_mapa(usuario, destino, n, m);

	/*Execução do mapa em si:*/	
	while(chegou != 1){
		printf("\n--------------------------------------------------\n");
		printf("Digite ENTER para o usuario correr atrás do destino: ");
		printf("\n--------------------------------------------------\n");
		getchar();
		
		/*Algoritmo de wavefront é aplicado no destino*/
		wavefront(G, (destino.y * m + destino.x), 1);

		/*Escolhe o vértice com a menor aresta conectada ao vértice atual do usuario.
		  Ou seja, escolhe o melhor caminho possível para percorrer.*/
		int verticeEscolhido = menor_vertice_adjacente(G, (usuario.y * m + usuario.x));
		
		//printf("vertice Escolhido: %d\n", verticeEscolhido);
		
		//Define as coordenadas de acordo com a lógica do vértice no mapa	
		usuario.y = verticeEscolhido / m;
		usuario.x = verticeEscolhido % m;
		
		//Mostra o mapa atualizado
		printf("\t---usuario ANDANDO---\n");
		imprimir_mapa(usuario, destino, n, m);

		
		//Se, ainda assim, não chegou, mostra o mapa atualizado
		if(usuario.x != destino.x || usuario.y != destino.y){	
			printf("\t---destino ANDANDO---\n");
			imprimir_mapa(usuario, destino, n, m);
			/*Insere todas as arestas que ligam os vértices(zera tudo denovo para um próximo wavefront)*/
			aresta = 0;
			for(int i=0; i<v; i++){
				int esquerda = i-1, direita = i+1, cima = i-m, baixo = i+m;

				//Insere conferindo se não está na borda do mapa para cada situação:
				if(i % m != 0) inserir_aresta(G, &i, &(esquerda), &aresta, &erro); //insere a esquerda
				if(i % m != (m-1)) inserir_aresta(G, &i, &(direita), &aresta, &erro); //insere a direita
				if(i >= m) inserir_aresta(G, &i, &(cima), &aresta, &erro); //insere em cima
				if(i < (m * n - n)) inserir_aresta(G, &i, &(baixo), &aresta, &erro); //insere em baixo
			}
		}else{
			chegou = 1;
			printf("\t---destino ANDANDO---\n");
			imprimir_mapa(usuario, destino, n, m);
		}
	}
	// GAME OVER
	printf("O usuario chegou O destino NA POSIÇÃO %dx%d. FIM DE mapa!\n", usuario.y, usuario.x);	
}	

/* Função imprimir_mapa: imprime o mapa do mapa com o usuario e o destino
@Argumentos: Posições do usuario e do destino, além das dimensões n e m do mapa
*/
void imprimir_mapa(Posicao usuario, Posicao destino, int n, int m){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(usuario.x == j && usuario.y == i) {printf("\033[0;31m");printf(" * ");printf("\033[0m");}
			else if(destino.x == j && destino.y == i) {printf("\033[0;32m");printf(" (X) ");printf("\033[0m");}
			else printf(" # ");
		}
		printf("\n");
	}
	printf("\n");
}

/* Função destino_caminha: escolhe uma nova posição aleatoriamente para o destino
@Argumentos: ponteiro para a posição do destino e dimensões do mapa
*/
void destino_caminha(Posicao *destino, int n, int m){
	int escolha, mudou = 0;
	do{
		escolha = rand() % 5;
		switch(escolha){
			case 1: 
				if(destino->x != m-1){
					destino->x++;
					mudou = 1;
				}
				break;
			case 2:
				if(destino->x != 0){
					destino->x--;
					mudou = 1;
				}
				break;
			case 3:
				if(destino->y != 0){
					destino->y--;
					mudou = 1;
				}
				break;
			case 4:
				if(destino->y != n-1){
					destino->y++;
					mudou = 1;
				}	
				break;
		}
	}while(!mudou);
}
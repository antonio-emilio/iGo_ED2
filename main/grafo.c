#include "grafo.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

grafo *criarGrafo()
{
	grafo *g = malloc(sizeof(grafo));
	g->espacoNo = 0;
	g->contadorNos = 0;
	g->nos = NULL;
	return g;
}

/*
	Verifica se o grafo esta cheio comparando o espaço com o contador.
*/
bool grafoCheio(grafo *g)
{
	return g->espacoNo == g->contadorNos;
}

/*
	Aumenta o tamanho do grafo.
*/
void aumentaGrafo(grafo *g)
{
	if (g->espacoNo == 0) /*Tamanho igual a zero?*/
	{
		g->espacoNo = 1;
	}
	else
	{
		g->espacoNo *= 2;
	}
	g->nos = realloc(g->nos, sizeof(no) * (g->espacoNo));
}

/*
	Adiciona um nó para o grafo.
*/
void adicionarNo(grafo *g, char *c)
{
	unsigned int contador;
	no *n;

	if (grafoCheio(g)) /*Verifica se o grafo esta cheio.*/
	{
		aumentaGrafo(g); /*Se estiver cheio, aumenta o seu tamanho.*/
	}

	contador = g->contadorNos;
	n = &g->nos[contador];
	n->nome = c;
	n->Vertices = NULL;
	n->contadorVertice = 0;
	n->espacoVertice = 0;
	n->distancia = INFINITY;
	n->indicePilha = -1;
	n->anterior = -1;

	g->contadorNos++;
}

/*
	Adiciona um vertice.
*/
void adicionaVertice(grafo *g, unsigned int i, unsigned int j, double pesoVertice)
{
	vertice *e;
	no *n;

	n = &g->nos[i];
	if (n->espacoVertice == n->contadorVertice)
	{
		if (n->espacoVertice == 0)
		{
			n->espacoVertice = 1;
		}
		else
		{
			n->espacoVertice *= 2;
		}
		n->Vertices = realloc(n->Vertices, sizeof(vertice) * (n->espacoVertice));
	}
	e = &n->Vertices[n->contadorVertice];
	e->origem = i;
	e->destino = j;
	e->pesoVertice = pesoVertice;
	g->nos[i].contadorVertice++;
}

/*
	Exclui o grafo.
*/
void liberaGrafo(grafo *g)
{
	unsigned int i;
	for (i = 0; i < g->contadorNos; i++)
	{
		free(g->nos[i].Vertices);
		free(g->nos[i].nome);
	}
	free(g->nos);
	free(g);
}

/*
	Imprime o resultado no console.
*/
void mostraCaminhos(grafo *g, int destinoMarcado, int modoDepuracao)
{
	unsigned int j;
	int i, contador;
	int index;
	int *indices;
	contador = (int)g->contadorNos;
	indices = NULL;

	if (destinoMarcado != -1)
	{
		indices = malloc(sizeof(int) * contador);
		for (i = 0; i < contador; i++)
		{
			indices[i] = -1;
		}
		index = destinoMarcado;
		while (g->nos[index].anterior != -1)
		{
			indices[index] = g->nos[index].anterior;
			index = (g->nos[index].anterior);
		}
	}

	for (i = 0; i < contador; i++)
	{
		for (j = 0; j < g->nos[i].contadorVertice; j++)
		{
			if (destinoMarcado != -1)
			{
				if (indices[g->nos[i].Vertices[j].destino] == i)
				{
					tempoEstimado += (int)g->nos[i].Vertices[j].pesoVertice;
					defineCor('g');
					printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
						   g->nos[i].nome,
						   g->nos[g->nos[i].Vertices[j].destino].nome,
						   (int)g->nos[i].Vertices[j].pesoVertice);

					defineCor('n');
				}
				else if (modoDepuracao == 1)
				{
					defineCor('r');
					printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
						   g->nos[i].nome,
						   g->nos[g->nos[i].Vertices[j].destino].nome,
						   (int)g->nos[i].Vertices[j].pesoVertice);

					defineCor('n');
				}
			}
			else
			{
				defineCor('b');
			}
		}
	}
	condicao = "Transito normal.";
	defineCor('b');
	printf("ETA total: %d min | Condicao: %s\n", tempoEstimado, condicao);
	defineCor('n');
}



/*
	Imprime o resultado no console.
*/
void mostraMapaTransito(grafo *g)
{
	unsigned int j;
	int i, contador;
	int index;
	int *indices;

	contador = (int)g->contadorNos;
	indices = NULL;


	for (i = 0; i < contador; i++)
	{
		for (j = 0; j < g->nos[i].contadorVertice; j++)
		{

			defineCor('b');
			printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
					g->nos[i].nome,
					g->nos[g->nos[i].Vertices[j].destino].nome,
					(int)g->nos[i].Vertices[j].pesoVertice);

			defineCor('n');

		}
	}
}



/*
	Retorna o indice da localizacao, recebendo como parametro o nome e retornando o indice.
*/
int indiceDoNome(grafo *g, char *nomeLocal)
{
	unsigned int j;
	int i, contador;
	int index;
	int *indices;

	contador = (int)g->contadorNos;
	indices = NULL;
	/*Procura por todos os vertices qual o indice referente ao nome inserido.*/
	for (i = 0; i < contador; i++)
	{

		if (!strcmp(g->nos[i].nome, nomeLocal))
		{
			return i;
		}
	}

	/*Se nao encontrou nada, retorna codigo de erro.*/
	return -1;
}
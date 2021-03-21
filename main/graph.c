#include "graph.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

graph *graph_make()
{
	graph *g = malloc(sizeof(graph));
	g->node_space = 0;
	g->node_count = 0;
	g->nodes = NULL;
	return g;
}

/*
	Verifica se o grafo esta cheio comparando o espaço com o contador.
*/
bool graph_is_full(graph *g)
{
	return g->node_space == g->node_count;
}

/*
	Aumenta o tamanho do grafo.
*/
void graph_enlarge(graph *g)
{
	if (g->node_space == 0) /*Tamanho igual a zero?*/
	{
		g->node_space = 1;
	}
	else
	{
		g->node_space *= 2;
	}
	g->nodes = realloc(g->nodes, sizeof(node) * (g->node_space));
}

/*
	Adiciona um nó para o grafo.
*/
void graph_add_node(graph *g, char *c)
{
	unsigned int count;
	node *n;

	if (graph_is_full(g)) /*Verifica se o grafo esta cheio.*/
	{
		graph_enlarge(g); /*Se estiver cheio, aumenta o seu tamanho.*/
	}

	count = g->node_count;
	n = &g->nodes[count];
	n->value = c;
	n->edges = NULL;
	n->edge_count = 0;
	n->edge_space = 0;
	n->distance = INFINITY;
	n->heap_index = -1;
	n->previous = -1;

	g->node_count++;
}

/*
	Adiciona um vertice.
*/
void adicionaVertice(graph *g, unsigned int i, unsigned int j, double weight)
{
	edge *e;
	node *n;

	n = &g->nodes[i];
	if (n->edge_space == n->edge_count)
	{
		if (n->edge_space == 0)
		{
			n->edge_space = 1;
		}
		else
		{
			n->edge_space *= 2;
		}
		n->edges = realloc(n->edges, sizeof(edge) * (n->edge_space));
	}
	e = &n->edges[n->edge_count];
	e->source = i;
	e->destination = j;
	e->weight = weight;
	g->nodes[i].edge_count++;
}

/*
	Exclui o grafo.
*/
void liberaGrafo(graph *g)
{
	unsigned int i;
	for (i = 0; i < g->node_count; i++)
	{
		free(g->nodes[i].edges);
		free(g->nodes[i].value);
	}
	free(g->nodes);
	free(g);
}

/*
	Imprime o resultado no console.
*/
void mostraCaminhos(graph *g, int highlight_destination)
{
	unsigned int j;
	int i, count;
	int index;
	int *indices;

	count = (int)g->node_count;
	indices = NULL;

	if (highlight_destination != -1)
	{
		indices = malloc(sizeof(int) * count);
		for (i = 0; i < count; i++)
		{
			indices[i] = -1;
		}
		index = highlight_destination;
		while (g->nodes[index].previous != -1)
		{
			indices[index] = g->nodes[index].previous;
			index = (g->nodes[index].previous);
		}
	}

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < g->nodes[i].edge_count; j++)
		{
			if (highlight_destination != -1)
			{
				if (indices[g->nodes[i].edges[j].destination] == i)
				{
					tempoEstimado += (int)g->nodes[i].edges[j].weight;
					defineCor('g');
					printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
						   g->nodes[i].value,
						   g->nodes[g->nodes[i].edges[j].destination].value,
						   (int)g->nodes[i].edges[j].weight);

					defineCor('n');
				}
				else if (modoDepuracao == 1)
				{
					defineCor('r');
					printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
						   g->nodes[i].value,
						   g->nodes[g->nodes[i].edges[j].destination].value,
						   (int)g->nodes[i].edges[j].weight);

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
void mostraMapaTransito(graph *g)
{
	unsigned int j;
	int i, count;
	int index;
	int *indices;

	count = (int)g->node_count;
	indices = NULL;


	for (i = 0; i < count; i++)
	{
		for (j = 0; j < g->nodes[i].edge_count; j++)
		{

			defineCor('b');
			printf("\"%s\" -> \"%s\" [ETA: %d min];\n",
					g->nodes[i].value,
					g->nodes[g->nodes[i].edges[j].destination].value,
					(int)g->nodes[i].edges[j].weight);

			defineCor('n');

		}
	}
}



/*
	Retorna o indice da localizacao, recebendo como parametro o nome e retornando o indice.
*/
int indiceDoNome(graph *g, char *nomeLocal)
{
	unsigned int j;
	int i, count;
	int index;
	int *indices;

	count = (int)g->node_count;
	indices = NULL;
	/*Procura por todos os vertices qual o indice referente ao nome inserido.*/
	for (i = 0; i < count; i++)
	{

		if (!strcmp(g->nodes[i].value, nomeLocal))
		{
			return i;
		}
	}

	/*Se nao encontrou nada, retorna codigo de erro.*/
	return -1;
}
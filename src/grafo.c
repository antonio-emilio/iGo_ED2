/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

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

int calculaTempoNormal(int origem2, int destino2)
{
	grafo *g2;
	FILE *f2, *a2;
	char buffer[100], aux[100], *temp;
	bool verticeIniciado;
	int maximoVRand = 10, minimoVRand = 0;
	double distancia;
	int distancia2, origem, destino;
	int modoDepuracao = 0; /*Modo depuracao para caso o usuario queira verificar todas as rotas existentes.*/
	char texto_str[1024], nomeArquivo[1024];
	FILE *arquivo;

	tempoEstimado = 0;

	g2 = criarGrafo();
	f2 = fopen("grafo.txt", "r");

	/* Construção do grafo. */
	while (fgets(buffer, 100, f2) != NULL)
	{
		if (!verticeIniciado)
		{
			if (*buffer == '\n')
			{
				continue;
			}
			if (strcmp(buffer, "---\n") == 0)
			{
				verticeIniciado = true;
				continue;
			}
			sscanf(buffer, "%d) %[^\n]", &origem, aux);
			temp = malloc(strlen(aux) + 1);
			strcpy(temp, aux);
			adicionarNo(g2, temp);
		}
		else
		{
			if (*buffer == '\n')
			{
				continue;
			}
			sscanf(buffer, "%d -> %d %lf\n", &origem, &destino, &distancia);
			adicionaVertice(g2, origem, destino, distancia);
		}
	}

	fclose(f2);

	dijkstra2(g2, origem2);
	int valor = mostraCaminhos2(g2, destino2, modoDepuracao, origem2);
	return valor;
}

/*
	Imprime o resultado no console.
*/
int mostraCaminhos(grafo *g, int destinoMarcado, int modoDepuracao, int origemMarcada)
{
	unsigned int j;
	int i, contador;
	int index;
	int *indices;
	contador = (int)g->contadorNos;
	indices = NULL;
	tempoEstimado = 0;

	/*Iniciando do destino, vai "voltando" no grafico até encontrar a origem e colocando num vetor por quais pontos ele passou.*/
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

	int tempoEstimadoAtual = tempoEstimado;
	int tempoNormal = calculaTempoNormal(origemMarcada, destinoMarcado);

	if (tempoEstimadoAtual == 0 && tempoNormal == 0)
	{
		defineCor('r');
		printf("Nao existem rotas possiveis para o trajeto informado.");
		defineCor('n');
	}
	else
	{

		if (tempoEstimadoAtual > tempoNormal)
		{
			condicao = "Transito moderado-pesado.";
			defineCor('r');
			printf("ETA total: %d min | Este trajeto geralmente e feito em %d min | Condicao: %s\n", tempoEstimadoAtual, tempoNormal, condicao);
			defineCor('n');
		}
		else
		{
			if (tempoEstimadoAtual == tempoNormal)
			{
				condicao = "Transito normal.";
				defineCor('b');
				printf("ETA total: %d min | Este trajeto geralmente e feito em %d min | Condicao: %s\n", tempoEstimadoAtual, tempoNormal, condicao);
				defineCor('n');
			}
			else
			{
				condicao = "Sem transito no seu trajeto.";
				defineCor('g');
				printf("ETA total: %d min | Este trajeto geralmente e feito em %d min | Condicao: %s\n", tempoEstimadoAtual, tempoNormal, condicao);
				defineCor('n');
			}
		}
	}

	return tempoEstimadoAtual;
}

int mostraCaminhos2(grafo *g, int destinoMarcado, int modoDepuracao, int origemMarcada)
{
	unsigned int j;
	int i, contador;
	int index;
	int *indices;
	contador = (int)g->contadorNos;
	indices = NULL;
	tempoEstimado = 0;

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
				}
			}
		}
	}

	return tempoEstimado;
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

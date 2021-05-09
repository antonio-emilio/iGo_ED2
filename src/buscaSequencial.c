#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INVALIDO -1
typedef struct
{
    int chave;
    int prox;
} ELEMENTOS;
typedef struct
{
    ELEMENTOS A[MAX];
    int dispo;
    int inicio;

} LISTA;

void inicializarEstrutura(LISTA *l)
{
    int i = 0;
    for (i = 0; i < MAX - 1; i++)
        l->A[i].prox = i + 1;
    l->A[MAX - 1].prox = INVALIDO;
    l->dispo = 0;
    l->inicio = INVALIDO;
}

void imprime(LISTA *l)
{
    int i = l->inicio;
    printf("Lista: ");
    while (i != INVALIDO)
    {
        printf(" %i ", l->A[i].chave);
        i = l->A[i].prox;
    }
}

int buscaSequencial(LISTA *l, int x)
{
    int i = l->inicio;
    while (i != INVALIDO && l->A[i].chave < x)
        i = l->A[i].prox;
    if (l->A[i].chave == x)
        return i;
    else
        return -1;
}

int obterNO(LISTA *l)
{
    int disponivel = l->dispo;
    if (l->dispo != INVALIDO)
    {
        l->dispo = l->A[l->dispo].prox;
    }
    return disponivel;
}

int inserirElementos(LISTA *l, int x)
{
    if (l->dispo == INVALIDO)
        return -1;
    int ant = INVALIDO;
    int i = l->inicio;
    while (i != INVALIDO && l->A[i].chave < x)
    {
        ant = i;
        i = l->A[i].prox;
    }
    i = obterNO(l);
    l->A[i].chave = x;
    if (ant == INVALIDO)
    {
        l->A[i].prox = l->inicio;

        l->inicio = i;
    }
    else
    {
        l->A[i].prox = l->A[ant].prox;
        l->A[ant].prox = i;
    }
}

int ExecutaBuscaSequencial(int valor)
{

    LISTA *l = (LISTA *)malloc(sizeof(LISTA));
    inicializarEstrutura(l);

    for (int i = 0; i < 10; i++)
    {
        inserirElementos(l, i);
    }
    imprime(l);

    int indice = buscaSequencial(l, valor);
    printf("\nValor esta no indice %d\n", indice);

    return valor;
}

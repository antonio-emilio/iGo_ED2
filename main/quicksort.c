/*#include <stdio.h>
#include <stdlib.h>

int n, cont = 0;

void troca(int *vetor, int i, int j)
{
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
    cont ++;
}

int partition(int *vetor, int inicio, int fim)
{
    int j;
    int pivot = vetor[fim];
    int i = inicio - 1, k;

    for (j = inicio; j <= fim - 1; j++)
    {
        if (vetor[j] < pivot)
        {
            i = i + 1;
            troca(vetor, i, j);
        }
        cont++;
    }
    troca(vetor, i + 1, fim);
    return (i + 1);
}

void quickSort(int *vetor, int inicio, int fim)
{
    int meio, k;

    if (inicio < fim)
    {
        meio = partition(vetor, inicio, fim);
        quickSort(vetor, inicio, meio - 1);
        quickSort(vetor, meio + 1, fim);
    }
    cont++;
}*/
/*
int main()
{
    int i;
    n = 1;
    cont = 0;
    while (cont != (n * n))
    {
        n = rand() % (1000 + 1 - 1) + 1;

        int *vetor = (int *)malloc(n * sizeof(int));

        for (i = 0; i < n; i++)
        {
            vetor[i] = (rand() % (65000 + 1 - 0) + 0);
        }

        quickSort(vetor, 0, n - 1);

      
        free(vetor);
        cont = 0;
        if( cont == (n * n)){
              printf("|Contador: %d - N: %d|", cont, n);
        for (i = 0; i < n; i++)
        {
            printf("%d ", vetor[i]);
        }
        printf("\n");
        }
    }

    return 0;
}*/

#include <stdio.h>
#include <string.h>
#define max 50 //Tamanho maximo
struct destino
{
    char a[8196];
};

void quicksort(struct destino items[], int left, int right); //function for quick sort

int doQuickSort()
{
    FILE *fp;
    int i = 0, k = 0, n;
    char fname[10], str[10], c;
    struct destino name[max];

    fp = fopen("locaisMapa.txt", "r"); //Abre o arquivo em modo de escrita.
    while ((c = getc(fp)) != EOF)
    {
        if (c == ' ')
        {
            str[i] = '\0';
            strcpy(name[k].a, str); //Copia a string nome por nome
            i = 0;
            k++;
        }
        else
        {
            str[i] = c;
            i++;
        }
    }
    fclose(fp);
    quicksort(name, 0, k - 1); //Chamando a função de quicksort

    for (i = 0; i <= k; i++)
    {
        printf("%s,", name[i].a); //Faz o pritn dos nomes ordenados.
    }

    return 0;
}
//Função para o quicksort
void quicksort(struct destino items[], int first, int last)
{
    int j, i, pivot;
    char temp[10];
    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;
        while (i < j)
        {
            while ((strcmp(items[i].a, items[pivot].a)) < 0)
                i++;
            while ((strcmp(items[j].a, items[pivot].a)) > 0)
                j--;

            if (i < j)
            {
                strcpy(temp, items[i].a); //Troca os valores
                strcpy(items[i].a, items[j].a);
                strcpy(items[j].a, temp);
            }
        }
        strcpy(temp, items[pivot].a);
        strcpy(items[pivot].a, items[j].a);
        strcpy(items[j].a, temp);
        quicksort(items, first, j - 1); //Chamada recursiva
        quicksort(items, j + 1, last);
    }
}
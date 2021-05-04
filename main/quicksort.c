#include <stdio.h>
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
}
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
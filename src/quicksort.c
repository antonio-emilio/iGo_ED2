/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Função para comparar duas strings.
*/
int cmpstr(void *v1, void *v2)
{
    char *a1 = *(char **)v1;
    char *a2 = *(char **)v2;
    return strcmp(a1, a2);
}

/*
Funçaõ para trocar dois elementos após uma comparação.
*/
void swap(void *v1, void *v2, int size)
{
    char buffer[size];
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

/*Executa o algoritmo completo de quicksort.*/
void _qsort(void *v, int size, int left, int right, int (*comp)(void *, void *))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    void *vl = (char *)(v + (left * size));
    void *vr = (char *)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++)
    {

        vt = (char *)(v + (i * size));
        if ((*comp)(vl, vt) > 0)
        {
            ++last;
            v3 = (char *)(v + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char *)(v + (last * size));
    swap(vl, v3, size);
    _qsort(v, size, left, last - 1, comp);
    _qsort(v, size, last + 1, right, comp);
}

int doQuickSort()
{

    FILE *fp;
    int k = 0, n;
    char *a;
    char *arr[1024];
    char *arr2[1024];
    fp = fopen("locaisMapa.txt", "r");
    while (fgets(arr, 1024, fp) != NULL)
        ;
    char *token = strtok(arr, " ");

    while (token != NULL)
    {
        strcpy(&arr2[k], &token);
        k++;
        token = strtok(NULL, " ");
    }

    fclose(fp);

    _qsort(arr2, sizeof(char *), 0, k - 1, (int (*)(void *, void *))(cmpstr));

    for (int i = 0; i < k; i++)
        printf("%s \n", arr2[i]);
}
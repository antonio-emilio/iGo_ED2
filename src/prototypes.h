/*
    iWay - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include <stdio.h>
/*
    iGo - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include <stdlib.h>
#include <string.h>
#include "globalvar.h"
#include "utils.c"
#include <stdbool.h>
#include "grafo.h"
#include "grafo.c"
#include "dijkstra.h"
#include "dijkstra.c"
#include "pilha.h"
#include "pilha.c"
#include <time.h>
#include "hash.c"
#include "buscaSequencial.c"
#include "quicksort.c"



/*Protótipo de funções*/
void defineCor(char c);
int doQuickSort(void);
void atualizaTransito(void);
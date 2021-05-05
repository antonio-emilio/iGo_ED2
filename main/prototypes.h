/*
    iWay - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globaldef.h"
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




/*Protótipo das funções*/
void defineCor(char c);
int *executeQuickSort (void);
void atualizaTransito(void);
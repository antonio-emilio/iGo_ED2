/*
    iWay - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "grafo.h"

/*Funções gerais*/

/*Função para definir a cor do texto a ser mostrado na tela.*/
void defineCor(char c)
{
    switch (c)
    {
    case 'r':
        printf("\033[0;31m"); //Define a cor do texto para vermelho
        break;
    case 'g':
        printf("\033[0;32m"); //Define a cor do texto para verde
        break;
    case 'b':
        printf("\033[0;34m"); //Define a cor do texto para azul
        break;
    case 'n':
        printf("\033[0m"); //Volta a cor do texto para branco
        break;
    }
}
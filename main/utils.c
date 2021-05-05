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

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

/*Funções gerais*/

/*Função para definir a cor do texto a ser mostrado na tela.*/
void defineCor(char c)
{
    switch (c)
    {
    case 'r':
        printf(ANSI_COLOR_RED); //Define a cor do texto para vermelho
        break;
    case 'g':
        printf(ANSI_COLOR_GREEN); //Define a cor do texto para verde
        break;
    case 'b':
        printf(ANSI_COLOR_BLUE); //Define a cor do texto para azul
        break;
    case 'n':
        printf(ANSI_COLOR_RESET); //Volta a cor do texto para branco
        break;
    }
}

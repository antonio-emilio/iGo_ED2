/*
    iWay - Caminhos inteligentes.
    Alunos: Melyssa Mariana Gomes Silva e Antonio Emilio Pereira
    Disciplina: Estrutura de Dados II
*/

#include "prototypes.h"

int main(){

     for (;;)
    {
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~iWay~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("                   * Caminhos inteligentes. *\n                    ");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("|Digite um numero correspondente no menu:                         |\n");
        printf("|1. Visualizar mapa;                                              |\n");
        printf("|2. Definir destino;                                              |\n");
        printf("|3. Verificar trânsito atual;                                     |\n");
        printf("|4. Visualizar últimos destinos;                                   |\n");
        printf("|5. Sair;                                   |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        scanf("%d",&escolha);

        switch(escolha){
            case 1: /*Visualizar mapa;*/
            break;

            case 2: /*Definir destino; */
            break;

            case 3: /*Verificar trânsito atual; */
            break;

            case 4: /*Visualizar últimos destinos;*/
            break;

            case 5: /*Sair;*/
            return 0;
            break;

        }

    }


    return 0;
}

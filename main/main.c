#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include <stdbool.h>
#include <string.h>
#include "grafo.h"
#include "grafo.c"
#include "dijkstra.h"
#include "dijkstra.c"
#include "pilha.h"
#include "pilha.c"
#include <time.h>

int main()
{
    grafo *g;

    FILE *f, *a;
    char buffer[100], aux[100], *temp;
    bool verticeIniciado;
    int origem, dest;
    int maximoVRand = 10, minimoVRand = 0;
    double distancia;
    int distancia2;
    int modoDepuracao = 0; /*Modo depuracao para caso o usuario queira verificar todas as rotas existentes.*/
    char texto_str[1024], nomeArquivo[1024];

    verticeIniciado = false;

    for (;;)
    {
        defineCor('g');
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~iGo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("                   * Caminhos inteligentes. *\n                    ");
        printf("|Digite um numero correspondente no menu:                         |\n");
        printf("|1. Calcular rota especifica;                                     |\n");
        printf("|2. Calcular rota da localizacao atual (INF-SAMAMBAIA);           |\n");
        printf("|3. Verificar mapa e transito atual;                              |\n");
        printf("|4. Visualizar ultimos destinos;                                  |\n");
        printf("|5. Modo de depuracao;                                            |\n");
        printf("|6. Apagar ultimos destinos;                                      |\n");
        printf("|7. Atualizar transito;                                           |\n");
        printf("|8. Sair;                                                         |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        defineCor('n');
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:

            printf("\n Onde voce esta?\n");
            scanf("%s", &nomeLocal);

            printf("\n Onde deseja ir?\n");
            scanf("%s", &nomeDestino);

            FILE *arquivo;

            //Abre o arquivo digitado no modo escrita.
            arquivo = fopen("ultimosDestinos.txt", "a");

            //Se o arquivo não foi criado, retorna erro e finaliza o programa.
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            //Armazena a string dentro do arquivo.
            fprintf(arquivo, "%s\n", &nomeDestino);

            //Fecha o arquivo.
            fclose(arquivo);

            tempoEstimado = 0;

            g = criarGrafo();
            f = fopen("grafo_cidade.txt", "r");

            /* Construção do grafo. */
            while (fgets(buffer, 100, f) != NULL)
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
                    adicionarNo(g, temp);
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    adicionaVertice(g, origem, dest, distancia);
                }
            }

            fclose(f);

            dijkstra(g, indiceDoNome(g, &nomeLocal));
            mostraCaminhos(g, indiceDoNome(g, &nomeDestino), modoDepuracao);

            break;

        case 2:
            printf("\n Onde deseja ir?\n");
            scanf("%s", &nomeDestino);

            tempoEstimado = 0;

            g = criarGrafo();
            f = fopen("grafo_cidade.txt", "r");

            /* Construção do grafo. */
            while (fgets(buffer, 100, f) != NULL)
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
                    adicionarNo(g, temp);
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    adicionaVertice(g, origem, dest, distancia);
                }
            }

            fclose(f);

            dijkstra(g, indiceDoNome(g, "INF-SAMAMBAIA"));
            mostraCaminhos(g, indiceDoNome(g, &nomeDestino), modoDepuracao);
            break;

        case 3:

            g = criarGrafo();
            f = fopen("grafo_cidade.txt", "r");

            /* Construção do grafo. */
            while (fgets(buffer, 100, f) != NULL)
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
                    adicionarNo(g, temp);
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    adicionaVertice(g, origem, dest, distancia);
                }
            }

            fclose(f);
            mostraMapaTransito(g);
            break;

        case 4:
            printf("\nUltimos destinos calculados:\n");
            //Abre o arquivo digitado no modo apenas leitura.
            arquivo = fopen("ultimosDestinos.txt", "r");

            //Se o arquivo não existe, retorna erro e finaliza o programa.
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            defineCor('b');

            //Enquanto o arquivo não chegar ao fim, fará o print das informações.
            while (fgets(texto_str, 1024, arquivo) != NULL)
                printf("%s", texto_str);

            defineCor('n');

            //Fecha o arquivo.
            fclose(arquivo);
            break;

        case 5:
            if (modoDepuracao)
            {
                modoDepuracao = 0;
                printf("\n Modo de depuracao DESATIVADO.\n");
            }
            else
            {
                modoDepuracao = 1;
                printf("\n Modo de depuracao ATIVADO.\n");
            }

            break;

        case 6:

            //Abre o arquivo digitado no modo escrita.
            arquivo = fopen("ultimosDestinos.txt", "w");

            //Se o arquivo não foi criado, retorna erro e finaliza o programa.
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            //Armazena a string dentro do arquivo.
            fprintf(arquivo, "");

            //Fecha o arquivo.
            fclose(arquivo);

            printf("\n Ultimos destinos apagados com SUCESSO.\n");

            break;

        case 7:

            //Utiliza a "data" atual para gerar numeros aleatorios.
            srand(time(0));

            //Abre o arquivo digitado no modo escrita.
            arquivo = fopen("grafo_cidade.txt", "w");

            //Se o arquivo não foi criado, retorna erro e finaliza o programa.
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            tempoEstimado = 0;

            g = criarGrafo();
            f = fopen("grafo.txt", "r");

            /* Construção do grafo. */
            while (fgets(buffer, 100, f) != NULL)
            {
                if (!verticeIniciado)
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    if (strcmp(buffer, "---\n") == 0)
                    {
                        fprintf(arquivo, "%s", &buffer);
                        verticeIniciado = true;
                        continue;
                    }
                    sscanf(buffer, "%d) %[^\n]", &origem, aux);
                    fprintf(arquivo, "%s", &buffer);
                    temp = malloc(strlen(aux) + 1);
                    strcpy(temp, aux);
                    adicionarNo(g, temp);
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    distancia2 = (rand() % (maximoVRand - minimoVRand + 1)) + minimoVRand;
                    sprintf(buffer, "%d -> %d %d\n", origem, dest, distancia2);
                    fprintf(arquivo, "%s", &buffer);
                    adicionaVertice(g, origem, dest, distancia);

                    
                }
            }

            fclose(f);
            fclose(arquivo);
            break;

        case 8:
            liberaGrafo(g);
            return 0;
            break;
        }
    }

    return 0;
}
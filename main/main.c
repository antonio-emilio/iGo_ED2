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
    int maximoVRand = 10, minimoVRand = 1;
    double distancia;
    int distancia2;
    int modoDepuracao = 0; /*Modo depuracao para caso o usuario queira verificar todas as rotas existentes.*/
    char texto_str[1024], nomeArquivo[1024];

    verticeIniciado = false;

    for (;;)
    {
        defineCor('b');
        printf("\n");
        printf("                                                        ******            \n"
               "                                                      ***********         \n"
               "                                                    ***************       \n"
               "                                                  ******************      \n"
               "   *****        **********             ********** ********************    \n"
               "             **          **         *           ********       *******    \n"
               "   *****   *    ******** *****     *    ******* *******        *******    \n"
               "   *   *   *   *                  *    *         *********    ********    \n"
               "   *   * *   *     ************ *   *            ********************     \n"
               "   *   * *   *     *         ** *   *           *  *****************      \n"
               "   *   *  *   **    ******    *   *   **        *   * *************       \n"
               "   *   *   *      ******    **     *     ******     * ***********         \n"
               "   *****     ***          **          *         *      ********           \n"
               "                 ********              *********         ******           \n"
               "                                                         ****             \n"
               "                                                          **              \n"
               "                                                                          \n");
               defineCor('g');

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~iGo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("                   * Caminhos inteligentes. *                      \n");
        printf("|Digite um numero correspondente no menu:                         |\n");
        printf("|1. Calcular rota especifica;                                     |\n");
        printf("|2. Calcular rota partindo do (INF-SAMAMBAIA);                    |\n");
        printf("|3. Verificar mapa e transito atual;                              |\n");
        printf("|4. Visualizar ultimos destinos;                                  |\n");
        printf("|5. Modo de depuracao;                                            |\n");
        printf("|6. Apagar ultimos destinos;                                      |\n");
        printf("|7. Atualizar transito;                                           |\n");
        printf("|8. Incluir ligacao no mapa;                                      |\n");
        printf("|9. Incluir local no mapa;                                        |\n");
        printf("|10. Sair;                                                        |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        defineCor('n');
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            /*
            Faz o cálculo de menor distância partindo de um ponto de origem e indo até um posto de destino.
            */
            printf("\nOnde voce esta?\n");
            scanf("%s", &nomeLocal);

            printf("\nOnde deseja ir?\n");
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
            mostraCaminhos(g, indiceDoNome(g, &nomeDestino), modoDepuracao,indiceDoNome(g, &nomeLocal));

            break;

        case 2:
            /*
            Faz o calculo de menor caminho partindo do INF-SAMAMBAIA.
            */
            printf("\nOnde deseja ir?\n");
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
            mostraCaminhos(g, indiceDoNome(g, &nomeDestino), modoDepuracao,indiceDoNome(g, &nomeLocal));
            break;

        case 3:
            /*
            Printa toda a cidade e seus respectivos pesos.
            */
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
            /*
            Faz a leitura do arquivo de ultimos registros inseridos no aplicativo.
            */
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
            /*
            Ativa o modo depuração para verificar todos os trajetos da cidade, ao invés de só o trajeto com o menor caminho.
            */
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
            /*
            Abre o arquivo no modo de escrita e insere um caractere nulo.
            */
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
            /*
            Faz a leitura do arquivo de referencia, copiando todo o conteudo para o arquivo de utilização.
            Ao copiar o valor referente ao peso do vértice, gera um valor aleatório dentro de um intervalo e coloca no lugar do valor antigo.
            */
            srand(time(0)); //Utiliza a "data" atual para gerar numeros aleatorios.

            arquivo = fopen("grafo_cidade.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            f = fopen("grafo.txt", "r");
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
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;
            printf("\nO TRANSITO FOI ATUALIZADO COM SUCESSO.\n");

            break;

        case 8:
            /*
            Para incluir uma nova ligação no mapa, primeiramente coletamos a origem e o destino.
            Depois disso, montamos o grafo lendo o arquivo para que seja possivel adquirir os numeros referente aos nomes que o usuario digitou.
            Logo, ao finalizar, escrevemos ao final do arquivo a nova conexao.
            */
            srand(time(0)); //Utiliza a "data" atual para gerar numeros aleatorios.

            printf("\n Digite o nome do local de origem da ligacao.\n");
            scanf("%s", &nomeLocal);

            printf("\n Digite o nome do local de destino da ligacao.\n");
            scanf("%s", &nomeDestino);

            distancia2 = (rand() % (maximoVRand - minimoVRand + 1)) + minimoVRand;

            g = criarGrafo();
            f = fopen("grafo.txt", "r");
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

            arquivo = fopen("grafo.txt", "a");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            sprintf(buffer, "%d -> %d %d", indiceDoNome(g, &nomeLocal), indiceDoNome(g, &nomeDestino), distancia2);
            fprintf(arquivo, "\n%s", &buffer);

            fclose(arquivo);
            verticeIniciado = false;

            arquivo = fopen("grafo_cidade.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            f = fopen("grafo.txt", "r");
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
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    fprintf(arquivo, "%s", &buffer);
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;

            arquivo = fopen("grafo_aux.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            f = fopen("grafo.txt", "r");
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
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    fprintf(arquivo, "%s", &buffer);
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;

            break;

        case 9:

            /*
            Para incluir uma nova localizacao, estamos utilizando um arquivo .txt auxiliar.
            Primeiro rodamos o arquivo de destinos pra descobrir a linha que se encontra a última localização
            Depois iniciamos a copia desse arquivo para o arquivo auxiliar, e quando chegamos na linha do ultimo registro, incluimos mais um registro.
            Ao finalizar, copiamos novamente o conteudo do arquivo auxiliar para o arquivo normal.
            */

            printf("\n Digite o nome da nova localizacao.\n");
            scanf("%s", &nomeLocal);

            f = fopen("grafo.txt", "r");
            int indiceSeparador = 0;

            while (fgets(buffer, 100, f) != NULL)
            {

                if (strcmp(buffer, "---\n") == 0)
                {
                    break;
                }
                indiceSeparador++;
            }
            fclose(f);

            indiceSeparador++;
            f = fopen("grafo.txt", "r");
            arquivo = fopen("grafo_aux.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            int contAux = 0;
            while (fgets(buffer, 100, f) != NULL)
            {
                contAux++;
                if (contAux == indiceSeparador)
                {
                    sprintf(buffer, "%d) %s\n---\n", indiceSeparador - 1, &nomeLocal);
                    fprintf(arquivo, "%s", &buffer);
                }
                else
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
                    }
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;

            arquivo = fopen("grafo.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            f = fopen("grafo_aux.txt", "r");
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
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    fprintf(arquivo, "%s", &buffer);
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;

            arquivo = fopen("grafo_cidade.txt", "w");
            if (arquivo == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return (0);
            }

            f = fopen("grafo.txt", "r");
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
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &origem, &dest, &distancia);
                    fprintf(arquivo, "%s", &buffer);
                }
            }

            fclose(f);
            fclose(arquivo);
            verticeIniciado = false;

            break;

        case 10:
            liberaGrafo(g);
            return 0;
            break;
        }
    }

    return 0;
}
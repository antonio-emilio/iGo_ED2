#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include <stdbool.h>
#include <string.h>
#include "graph.h"
#include "graph.c"
#include "dijkstra.h"
#include "dijkstra.c"
#include "heap.h"
#include "heap.c"

int main()
{
    graph *g;

    FILE *f;
    char buffer[100], ciudad[100], *ciudad_tmp;
    bool started_vertices;
    int src, dest;
    double distance;

    started_vertices = false;

    for (;;)
    {
        defineCor('g');
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~iWay~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("                   * Caminhos inteligentes. *\n                    ");
        printf("|Digite um numero correspondente no menu:                         |\n");
        printf("|1. Calcular rota;                                                |\n");
        printf("|2. Visualizar mapa;                                              |\n");
        printf("|3. Verificar transito atual;                                     |\n");
        printf("|4. Visualizar ultimos destinos;                                  |\n");
        printf("|5. Atualizar transito;                                           |\n");
        printf("|6. Sair;                                                         |\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        defineCor('n');
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:

            printf("\n Onde voce esta?\n");
            scanf("%d", &indexInicio);

            printf("\n Onde deseja ir?\n");
            scanf("%d", &indexDestino);

            tempoEstimado = 0;

            g = graph_make();
            f = fopen("grafo.txt", "r");

            /* Construção do grafo. */
            while (fgets(buffer, 100, f) != NULL)
            {
                if (!started_vertices)
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    if (strcmp(buffer, "---\n") == 0)
                    {
                        started_vertices = true;
                        continue;
                    }
                    sscanf(buffer, "%d) %[^\n]", &src, ciudad);
                    ciudad_tmp = malloc(strlen(ciudad) + 1);
                    strcpy(ciudad_tmp, ciudad);
                    graph_add_node(g, ciudad_tmp);
                }
                else
                {
                    if (*buffer == '\n')
                    {
                        continue;
                    }
                    sscanf(buffer, "%d -> %d %lf\n", &src, &dest, &distance);
                    graph_add_edge(g, src, dest, distance);
                }
            }

            dijkstra(g, indexInicio);
            graph_dump(g, indexDestino);
            graph_destroy(g);
            break;

        case 2:
            printf("\n Funcao ainda nao implementada.\n");
            break;

        case 3:
            printf("\n Funcao ainda nao implementada.\n");
            break;

        case 4:
            printf("\n Funcao ainda nao implementada.\n");
            break;

        case 5:
            printf("\n Funcao ainda nao implementada.\n");
            break;

        case 6:
            return 0;
            break;
        }
    }

    return 0;
}
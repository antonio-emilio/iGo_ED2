# iWay

<img src="https://cdn.discordapp.com/attachments/764880223560794172/825332830514446336/9lhpx3wZUgfWAJPjYc-33Bs3E0ZWiHseTUBVy9_2oZjdMjyIQFbQAZgQAV8PAzLs-si4k-w9ZEpb7pPaygrtmGY1mPib5M9GtAv6.png">


## Proposta
Desenvolver o algoritmo utilizado no GPS atualmente. Consiste basicamente de um sistema de grafos denomidados "Cidade", ao qual será possível escolher dentre vários mapas. Dentro de cada mapa, o usuário poderá escolher até qual ponto ele deseja se locomover. Assim que a entrada de dados é processada, o algoritmo de Dijkstra busca qual é o percurso com menor tempo possível, retornando as rotas para o usuário.


## Funcionalidades
* Selecionar mapa
* Mostrar mapa
* Ver tráfego atual do mapa
* Definir destino
* Obter melhor rota


## Tecnologia
Utilizará a linguagem de programação C. Será utilizado os conceitos de  Tipo Abstrato de Dados, grafos, busca e etc. 

## Autores
* Melyssa Mariana Gomes Silva;
* Antonio Emílio Pereira;

## Estruturas
  ### Grafos

| nome                  | tipo                          | descrição                                                 |
| -------------         | -----------                   | ---                                                       |
| Nós                   | Lista encadeada de nós        | Lista de nós que compoem o grafo                          |
| Contagem do nó        | int                           | Contador atrelado aos nós                                 |
| Tamanho do nó         | int                           | Tamanho alocado para o nó                                 |

  ### Nós

| nome                  | tipo                          | descrição                                                 |
| -------------         | -----------                   | ---                                                       |
| Vértices              | Lista encadeada de vétices    | Lista de vértices que compoem o nó                        |
| Contagem de vértices  | int                           | Contador de vértices                                      |
| Tamanho do vértice    | int                           | Tamanho alocado para o vértice                            |
| Nome do nó            | Ponteiro de char              | Nome de identificação do nó                               |

  ### Vértices

| nome                  | tipo                          | descrição                                                 |
| -------------         | -----------                   | ---                                                       |
| Origem                | Ponteiro de nós               | Indicação do nó de origem                                 |
| Destino               | Ponteiro de nós               | Indicação do nó de destino                                |
| Peso                  | int                           | Peso atrelado ao vértice                                  |


  ### Pilha

| nome                  | tipo                          | descrição                                                 |
| -------------         | -----------                   | ---                                                       |
| Nós                   | Ponteiro de nós               | Indicação do nó do topo                                   |
| Tamanho               | int                           | Indicação da quantidade máxima                            |
| Contador              | int                           | Indicação da quantidade atual                             |
| Grafo                 | Ponteiro de grafo             | Grafo ao qual se refere a pilha                           |



Ambos alunos de Engenharia de Computação, da Universidade Federal de Goiás.





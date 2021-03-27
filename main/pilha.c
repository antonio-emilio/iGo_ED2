#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

pilha* criaPilha(comparaPilha* cmp, grafo* g) {
	unsigned int i;
    pilha* h = malloc(sizeof(pilha));
    h->nos = malloc(sizeof(no) * (g->contadorNos) * 2);
    h->comparar = cmp;
    h->espaco = g->contadorNos * 2; 
    h->contador = 0;
	h->g = g;
	for(i = 0; i < g->contadorNos; i++) {
		inserePilha(h, i);
	}
    return h;
}

bool pilhaCheia(const pilha* h) {
    return h->contador == h->espaco;
}

void heap_enlarge(pilha* h) {
    if(h->espaco) { h->espaco *= 2; } else { h->espaco = 1; }
    h->nos = realloc(h->nos, sizeof(unsigned int) * (h->espaco)); 
}

void aumentaPrioridade(pilha* h, unsigned int indice) {
    unsigned int nome = h->nos[indice],
                 temp;
    while(indice != 0 && (*h->comparar)(h->g, nome, h->nos[PILHA_PAI(indice)]) < 0) {
        temp = h->nos[PILHA_PAI(indice)];
        h->nos[PILHA_PAI(indice)] = nome;
		h->g->nos[temp].indicePilha = indice;
		
        h->nos[indice] = temp;    
		h->g->nos[nome].indicePilha = PILHA_PAI(indice);
        indice = PILHA_PAI(indice); 
        nome = h->nos[indice];		
		
    } 
}

void heap_heapify_down(pilha* h) {
    unsigned int pos = 0, 
                 newpos,
                 temp;
	no** graph_nodes;

	graph_nodes = &h->g->nos;
	
    while(1) {
        if(PILHA_ESQUERDA(pos) <= h->contador) { 
            if(PILHA_DIREITA(pos) <= h->contador) {
                newpos = (*h->comparar)(h->g, h->nos[PILHA_DIREITA(pos)], h->nos[PILHA_ESQUERDA(pos)]) < 0 ? PILHA_DIREITA(pos) : PILHA_ESQUERDA(pos);
            } else {
                newpos = PILHA_ESQUERDA(pos);
            }
        } else {
            break; 
        }
        
        if((*h->comparar)(h->g, h->nos[pos], h->nos[newpos]) > 0) {
            temp = h->nos[pos];
			(*graph_nodes)[temp].indicePilha = newpos;
			(*graph_nodes)[h->nos[newpos]].indicePilha = pos;
            h->nos[pos] = h->nos[newpos];
            h->nos[newpos] = temp;
        } else {
            break; /*A posição está correta. */
        }
    }
}

void inserePilha(pilha* h, const unsigned int indice) {
    if(pilhaCheia(h)) { 
        heap_enlarge(h); 
    }
    h->nos[h->contador] = indice;
	h->g->nos[indice].indicePilha = h->contador;
    h->contador++;
    aumentaPrioridade(h, h->contador-1);
}

unsigned int encontraMinPilha(const pilha* h) {
    return h->nos[0];
}


unsigned int deletaMinPilha(pilha* h) {
    unsigned int retval = h->nos[0];
    
    h->nos[0] = h->nos[h->contador-1];
    h->contador--;
    if(pilhaVazia(h)) {
        free(h->nos);
    } else {
        heap_heapify_down(h);
    }
    return retval;
}

void imprimePilha(const pilha* h, const unsigned int from) {
    if(from == 0) {
        printf("digraph g {\nnode [shape = record,height=.1];\n");
    }
    if(from < h->contador) {
        printf("no%d[ label = \"<f0> | <f1> %s | <f2>\"];\n", from, h->g->nos[h->nos[from]].nome);

        if(PILHA_ESQUERDA(from) < h->contador) {
            printf("\"no%d\":f0 -> \"no%d\":f1\n", from, PILHA_ESQUERDA(from));
            imprimePilha(h, PILHA_ESQUERDA(from));
        }
    
        if(PILHA_DIREITA(from) < h->contador) {
            printf("\"no%d\":f2 -> \"no%d\":f1\n", from, PILHA_DIREITA(from));
            imprimePilha(h, PILHA_DIREITA(from));
        }
    }
    
    if(from == 0) { 
        printf("}\n");
    }
}

void destroiPilha(pilha* h) {
    if(!pilhaVazia(h)) {
        free(h->nos);
    }
    free(h);
}

bool pilhaVazia(const pilha* h) {
    return h->contador == 0;
}

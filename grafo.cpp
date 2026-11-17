#include "grafo.h"
#include <stdio.h>

void construirGrafo(Grafo *grafo)
{
    int i;
    int j;

    grafo->nomes[BLOCO_A] = "Bloco A";
    grafo->nomes[BLOCO_B] = "Bloco B";
    grafo->nomes[LABORATORIO] = "Laboratorio";
    grafo->nomes[REFEITORIO] = "Refeitorio";
    grafo->nomes[BIBLIOTECA] = "Biblioteca";

    for (i = 0; i < NUM_PREDIOS; i++) {
        for (j = 0; j < NUM_PREDIOS; j++) {
            grafo->adjacencia[i][j] = 0;
        }
    }

    grafo->adjacencia[BLOCO_B][LABORATORIO] = 240;
    grafo->adjacencia[LABORATORIO][BLOCO_B] = 240;

    grafo->adjacencia[LABORATORIO][BLOCO_A] = 210;
    grafo->adjacencia[BLOCO_A][LABORATORIO] = 210;

    grafo->adjacencia[BLOCO_A][REFEITORIO] = 190;
    grafo->adjacencia[REFEITORIO][BLOCO_A] = 190;

    grafo->adjacencia[REFEITORIO][BIBLIOTECA] = 280;
    grafo->adjacencia[BIBLIOTECA][REFEITORIO] = 280;

    grafo->adjacencia[BIBLIOTECA][BLOCO_A] = 160;
    grafo->adjacencia[BLOCO_A][BIBLIOTECA] = 160;
}
void dijkstra(const Grafo *g, int origem, int dist[], int anterior[])
{
    int visitado[NUM_PREDIOS];
    int i, rodada, u, v, menor;

    for (i = 0; i < NUM_PREDIOS; i++) {
        dist[i] = INFINITO;
        anterior[i] = -1;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    for (rodada = 0; rodada < NUM_PREDIOS; rodada++) {

        u = -1;
        menor = INFINITO;
        for (i = 0; i < NUM_PREDIOS; i++) {
            if (visitado[i] == 0 && dist[i] < menor) {
                menor = dist[i];
                u = i;
            }
        }
        if (u == -1) {
            break;
        }

        visitado[u] = 1;

        for (v = 0; v < NUM_PREDIOS; v++) {
            if (g->adjacencia[u][v] > 0 && visitado[v] == 0 &&
                dist[u] + g->adjacencia[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adjacencia[u][v];
                anterior[v] = u;
            }
        }
    }
}

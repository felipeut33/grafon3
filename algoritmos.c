/* Brayan Marques Eger, Jonathan Felipe Dinis Kovaleski, Felipe Utpadel e Samuel Lampert Alchini */

#include "algoritmos.h"

/* Dijkstra: menor distancia da origem ate todos os vertices.
 * dist[v]     = menor distancia (INFINITO se inalcancavel)
 * anterior[v] = predecessor de v no menor caminho (-1 se nao houver) */
void dijkstra(const Grafo *grafo, int origem, int dist[], int anterior[])
{
    int visitado[MAX_VERTICES];
    int i, rodada, u, v, menor;

    for (i = 0; i < grafo->quantidade; i++) {
        dist[i] = INFINITO;
        anterior[i] = -1;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    for (rodada = 0; rodada < grafo->quantidade; rodada++) {

        /* escolhe o vertice nao visitado com menor distancia */
        u = -1;
        menor = INFINITO;
        for (i = 0; i < grafo->quantidade; i++) {
            if (visitado[i] == 0 && dist[i] < menor) {
                menor = dist[i];
                u = i;
            }
        }
        if (u == -1) {
            break; /* restantes sao inalcancaveis */
        }

        visitado[u] = 1;

        /* relaxa as arestas que saem de u */
        for (v = 0; v < grafo->quantidade; v++) {
            if (grafo->matriz[u][v] > 0 && visitado[v] == 0 &&
                dist[u] + grafo->matriz[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo->matriz[u][v];
                anterior[v] = u;
            }
        }
    }
}

/* Floyd-Warshall: menores distancias entre todos os pares.
 * Ao final, alcancabilidade[i][j] = 1 se existe caminho de i ate j. */
void floydWarshall(const Grafo *grafo,
                   int dist[MAX_VERTICES][MAX_VERTICES],
                   int alcancabilidade[MAX_VERTICES][MAX_VERTICES])
{
    int i, j, k;
    int n = grafo->quantidade;

    /* matriz inicial W a partir da matriz de adjacencia */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (grafo->matriz[i][j] > 0) {
                dist[i][j] = grafo->matriz[i][j];
            } else {
                dist[i][j] = INFINITO;
            }
        }
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] != INFINITO && dist[k][j] != INFINITO &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            alcancabilidade[i][j] = (dist[i][j] != INFINITO) ? 1 : 0;
        }
    }
}

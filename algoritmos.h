/* Brayan Marques Eger, Jonathan Felipe Dinis Kovaleski, Felipe Utpadel e Samuel Lampert Alchini */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

void dijkstra(const Grafo *grafo, int origem, int dist[], int anterior[]);
void floydWarshall(const Grafo *grafo,
                   int dist[MAX_VERTICES][MAX_VERTICES],
                   int alcancabilidade[MAX_VERTICES][MAX_VERTICES]);

#endif

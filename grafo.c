/* Brayan Marques Eger, Jonathan Felipe Dinis Kovaleski, Felipe Utpadel e Samuel Lampert Alchini */

#include <string.h>

#include "grafo.h"

void construirGrafo(Grafo *grafo)
{
    int i;
    int j;

    grafo->quantidade = NUM_PREDIOS;

    strcpy(grafo->nomes[BLOCO_B], "Bloco B");
    strcpy(grafo->nomes[LABORATORIO], "Laboratorio");
    strcpy(grafo->nomes[BLOCO_A], "Bloco A");
    strcpy(grafo->nomes[REFEITORIO], "Refeitorio");
    strcpy(grafo->nomes[BIBLIOTECA], "Biblioteca");

    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            grafo->matriz[i][j] = 0;
        }
    }

    adicionarAresta(grafo, BLOCO_B, LABORATORIO, 240);
    adicionarAresta(grafo, LABORATORIO, BLOCO_A, 210);
    adicionarAresta(grafo, BLOCO_A, REFEITORIO, 190);
    adicionarAresta(grafo, REFEITORIO, BIBLIOTECA, 280);
    adicionarAresta(grafo, BIBLIOTECA, BLOCO_A, 160);
}

/* Grafo nao direcionado: grava o peso nos dois sentidos */
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso)
{
    if (origem < 0 || origem >= grafo->quantidade ||
        destino < 0 || destino >= grafo->quantidade || peso <= 0) {
        return;
    }

    grafo->matriz[origem][destino] = peso;
    grafo->matriz[destino][origem] = peso;
}

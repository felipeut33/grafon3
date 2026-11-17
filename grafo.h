#ifndef GRAFO_H
#define GRAFO_H

#define NUM_PREDIOS 5
#define INFINITO 1000000000

enum Predio {
    BLOCO_A,
    BLOCO_B,
    LABORATORIO,
    REFEITORIO,
    BIBLIOTECA
};

typedef struct {
    const char *nomes[NUM_PREDIOS];
    int adjacencia[NUM_PREDIOS][NUM_PREDIOS];
} Grafo;

void construirGrafo(Grafo *grafo);
void dijkstra(const Grafo *g, int origem, int dist[], int anterior[]);

#endif
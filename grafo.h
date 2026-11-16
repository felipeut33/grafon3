#ifndef GRAFO_H
#define GRAFO_H

#define NUM_PREDIOS 5

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

#endif

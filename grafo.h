/* Brayan Marques Eger, Jonathan Felipe Dinis Kovaleski, Felipe Utpadel e Samuel Lampert Alchini */

#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VERTICES 10
#define MAX_NOME 50
#define INFINITO 1000000000

/* Indices dos predios na matriz de adjacencia */
enum Predio {
    BLOCO_B,
    LABORATORIO,
    BLOCO_A,
    REFEITORIO,
    BIBLIOTECA,
    NUM_PREDIOS
};

/* Grafo ponderado e nao direcionado representado por matriz de adjacencia.
 * matriz[i][j] = distancia em metros entre i e j (0 = sem conexao direta). */
typedef struct {
    int quantidade;
    char nomes[MAX_VERTICES][MAX_NOME];
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

void construirGrafo(Grafo *grafo);
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso);

#endif

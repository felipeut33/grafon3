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

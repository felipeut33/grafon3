#include <stdlib.h>
#include <stdio.h>



#define INF 999999
#define MAX 100



void FloydWarshall(int W[MAX][MAX], int V) {



    int k, i, j;



    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {



                if (W[i][k] != INF && W[k][j] != INF &&
                    W[i][k] + W[k][j] < W[i][j]) {



                    W[i][j] = W[i][k] + W[k][j];



                }
            }
        }
    }
}



int main(void) {



    int V = 3;
    int i, j;



    int W[MAX][MAX] = {
        {0,   7,   15},
        {7,   0,   3},
        {15,  3,   0}
    };



    FloydWarshall(W, V);



    printf("Matriz de menores distancias:\n\n");



    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {



            if (W[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", W[i][j]);
            }



        }
        printf("\n");
    }



    printf("\nMatriz de alcancabilidade:\n\n");



    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {



            if (W[i][j] != INF) {
                printf("1 ");
            } else {
                printf("0 ");
            }



        }
        printf("\n");
    }



    return 0;
}

/* Brayan Marques Eger, Jonathan Felipe Dinis Kovaleski, Felipe Utpadel e Samuel Lampert Alchini */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#include "grafo.h"
#include "algoritmos.h"


int lerLinha(char texto[], int tamanho);
void removerEspacos(char texto[]);
int lerInteiro(const char *mensagem, int *valor);
int lerTexto(const char *mensagem, char texto[], int tamanho);
int compararSemDiferenciarCaixa(const char texto1[], const char texto2[]);

void exibirMenu(void);
void exibirMapa(const Grafo *grafo);
int selecionarPredio(const Grafo *grafo, const char *tipo);
void encontrarMenorRota(const Grafo *grafo);
void verificarConexao(const Grafo *grafo,
                      int alcancabilidade[MAX_VERTICES][MAX_VERTICES]);
void exibirMatrizAlcancabilidade(
    const Grafo *grafo,
    int alcancabilidade[MAX_VERTICES][MAX_VERTICES]);


int lerLinha(char texto[], int tamanho)
{
    int caractere;

    if (fgets(texto, tamanho, stdin) == NULL) {
        return 0;
    }

    if (strchr(texto, '\n') != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    } else {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
         
        }
    }

    return 1;
}


void removerEspacos(char texto[])
{
    char *inicio;
    size_t tamanho;

    inicio = texto;

    while (*inicio != '\0' && isspace((unsigned char)*inicio)) {
        inicio++;
    }

    if (inicio != texto) {
        memmove(texto, inicio, strlen(inicio) + 1);
    }

    tamanho = strlen(texto);

    while (tamanho > 0 && isspace((unsigned char)texto[tamanho - 1])) {
        texto[tamanho - 1] = '\0';
        tamanho--;
    }
}


int lerInteiro(const char *mensagem, int *valor)
{
    char entrada[100];
    char *fim;
    long numero;

    while (1) {
        printf("%s", mensagem);

        if (!lerLinha(entrada, sizeof(entrada))) {
            return 0;
        }

        errno = 0;
        numero = strtol(entrada, &fim, 10);

        while (*fim != '\0' && isspace((unsigned char)*fim)) {
            fim++;
        }

        if (entrada[0] == '\0' || fim == entrada || *fim != '\0' ||
            errno == ERANGE || numero < INT_MIN || numero > INT_MAX) {
            printf("Entrada invalida. Digite um numero inteiro.\n\n");
        } else {
            *valor = (int)numero;
            return 1;
        }
    }
}


int lerTexto(const char *mensagem, char texto[], int tamanho)
{
    while (1) {
        printf("%s", mensagem);

        if (!lerLinha(texto, tamanho)) {
            return 0;
        }

        removerEspacos(texto);

        if (texto[0] != '\0') {
            return 1;
        }

        printf("O valor nao pode ficar vazio. Tente novamente.\n\n");
    }
}


int compararSemDiferenciarCaixa(const char texto1[], const char texto2[])
{
    int caractere1;
    int caractere2;

    while (*texto1 != '\0' && *texto2 != '\0') {
        caractere1 = tolower((unsigned char)*texto1);
        caractere2 = tolower((unsigned char)*texto2);

        if (caractere1 != caractere2) {
            return caractere1 - caractere2;
        }

        texto1++;
        texto2++;
    }

    caractere1 = tolower((unsigned char)*texto1);
    caractere2 = tolower((unsigned char)*texto2);

    return caractere1 - caractere2;
}


void exibirMenu(void)
{
    printf("\n============================================================\n");
    printf("                 SISTEMA DE ROTAS DO CAMPUS\n");
    printf("============================================================\n\n");
    printf("1 - Exibir mapa do campus\n");
    printf("2 - Encontrar menor rota entre dois predios\n");
    printf("3 - Verificar conexao entre dois predios\n");
    printf("4 - Exibir matriz de alcancabilidade\n");
    printf("0 - Sair\n\n");
}


void exibirMapa(const Grafo *grafo)
{
    int i;
    int j;
    int encontrouAresta;

    printf("\n========== MAPA DO CAMPUS ==========\n");
    printf("Predios cadastrados:\n");

    for (i = 0; i < grafo->quantidade; i++) {
        printf("%d - %s\n", i + 1, grafo->nomes[i]);
    }

    printf("\nConexoes e distancias:\n");
    encontrouAresta = 0;

    for (i = 0; i < grafo->quantidade; i++) {
        for (j = i + 1; j < grafo->quantidade; j++) {
            if (grafo->matriz[i][j] > 0) {
                printf("%s <-> %s : %d m\n",
                       grafo->nomes[i],
                       grafo->nomes[j],
                       grafo->matriz[i][j]);
                encontrouAresta = 1;
            }
        }
    }

    if (!encontrouAresta) {
        printf("Nenhuma conexao cadastrada.\n");
    }

    printf("====================================\n");
}


int selecionarPredio(const Grafo *grafo, const char *tipo)
{
    char entrada[MAX_NOME + 20];
    char *fim;
    long numero;
    int i;

    while (1) {
        printf("\nPredios disponiveis:\n");

        for (i = 0; i < grafo->quantidade; i++) {
            printf("%d - %s\n", i + 1, grafo->nomes[i]);
        }

        printf("Digite o numero ou o nome do predio de %s.\n", tipo);

        if (!lerTexto("Selecao: ", entrada, sizeof(entrada))) {
            return -1;
        }

        numero = strtol(entrada, &fim, 10);

        while (*fim != '\0' && isspace((unsigned char)*fim)) {
            fim++;
        }


        if (fim != entrada && *fim == '\0') {
            if (numero >= 1 && numero <= grafo->quantidade) {
                return (int)numero - 1;
            }

            printf("Numero invalido. Escolha um numero entre 1 e %d.\n",
                   grafo->quantidade);
        } else {
        
            for (i = 0; i < grafo->quantidade; i++) {
                if (compararSemDiferenciarCaixa(entrada,
                                                grafo->nomes[i]) == 0) {
                    return i;
                }
            }

            printf("Predio nao encontrado. Digite o nome exatamente como listado.\n");
        }
    }
}


void encontrarMenorRota(const Grafo *grafo)
{
    int origem;
    int destino;
    int distancias[MAX_VERTICES];
    int predecessores[MAX_VERTICES];
    int caminho[MAX_VERTICES];
    int quantidadeCaminho;
    int atual;
    int i;

    printf("\n========== MENOR ROTA (DIJKSTRA) ==========\n");

    origem = selecionarPredio(grafo, "origem");
    if (origem == -1) {
        printf("Operacao cancelada.\n");
        return;
    }

    destino = selecionarPredio(grafo, "destino");
    if (destino == -1) {
        printf("Operacao cancelada.\n");
        return;
    }

    dijkstra(grafo, origem, distancias, predecessores);

    if (distancias[destino] >= INFINITO) {
        printf("Nao existe caminho entre %s e %s.\n",
               grafo->nomes[origem], grafo->nomes[destino]);
        return;
    }

    quantidadeCaminho = 0;
    atual = destino;

    while (atual != -1 && quantidadeCaminho < grafo->quantidade) {
        caminho[quantidadeCaminho] = atual;
        quantidadeCaminho++;

        if (atual == origem) {
            break;
        }

        atual = predecessores[atual];
    }

    if (quantidadeCaminho == 0 || caminho[quantidadeCaminho - 1] != origem) {
        printf("Nao foi possivel reconstruir a rota retornada por Dijkstra.\n");
        printf("Verifique a implementacao do vetor de predecessores.\n");
        return;
    }

    printf("Menor rota: ");

    for (i = quantidadeCaminho - 1; i >= 0; i--) {
        printf("%s", grafo->nomes[caminho[i]]);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\nDistancia total: %d metros\n", distancias[destino]);
    printf("===========================================\n");
}


void verificarConexao(const Grafo *grafo,
                      int alcancabilidade[MAX_VERTICES][MAX_VERTICES])
{
    int origem;
    int destino;

    printf("\n========== VERIFICAR CONEXAO ==========\n");

    origem = selecionarPredio(grafo, "origem");
    if (origem == -1) {
        printf("Operacao cancelada.\n");
        return;
    }

    destino = selecionarPredio(grafo, "destino");
    if (destino == -1) {
        printf("Operacao cancelada.\n");
        return;
    }

    if (alcancabilidade[origem][destino] == 1) {
        printf("Existe caminho entre %s e %s.\n",
               grafo->nomes[origem], grafo->nomes[destino]);
    } else {
        printf("Nao existe caminho entre %s e %s.\n",
               grafo->nomes[origem], grafo->nomes[destino]);
    }

    printf("=======================================\n");
}


void exibirMatrizAlcancabilidade(
    const Grafo *grafo,
    int alcancabilidade[MAX_VERTICES][MAX_VERTICES])
{
    int i;
    int j;

    printf("\n========== MATRIZ DE ALCANCABILIDADE ==========\n");
    printf("1 = existe caminho; 0 = nao existe caminho.\n\n");

    printf("%18s", " ");
    for (j = 0; j < grafo->quantidade; j++) {
        printf("%18.18s", grafo->nomes[j]);
    }
    printf("\n");

    for (i = 0; i < grafo->quantidade; i++) {
        printf("%18.18s", grafo->nomes[i]);

        for (j = 0; j < grafo->quantidade; j++) {
            printf("%18d", alcancabilidade[i][j]);
        }

        printf("\n");
    }

    printf("================================================\n");
}

int main(void)
{
    Grafo campus;
    int matrizDistanciasFloyd[MAX_VERTICES][MAX_VERTICES];
    int matrizAlcancabilidade[MAX_VERTICES][MAX_VERTICES];
    int opcao;

    construirGrafo(&campus);

    floydWarshall(&campus, matrizDistanciasFloyd, matrizAlcancabilidade);

    do {
        exibirMenu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            printf("\nEntrada encerrada. Finalizando o sistema.\n");
            break;
        }

        switch (opcao) {
            case 1:
                exibirMapa(&campus);
                break;

            case 2:
                encontrarMenorRota(&campus);
                break;

            case 3:
                verificarConexao(&campus, matrizAlcancabilidade);
                break;

            case 4:
                exibirMatrizAlcancabilidade(&campus, matrizAlcancabilidade);
                break;

            case 0:
                printf("Encerrando o Sistema de Rotas do Campus...\n");
                break;

            default:
                printf("Opcao invalida. Escolha uma opcao do menu.\n");
        }

    } while (opcao != 0);

    return 0;
}

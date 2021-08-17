
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#ifndef __FAT_LU_H__
#define __FAT_LU_H__

typedef double * MatRow;

// Estrutura para armazenar uma matriz A, decompola em LU  a fim de calcular a matriz inversa
typedef struct
{
    unsigned int n;       // Ordem da matriz
    double **A;           // matrix A
    double **L;           // L*U =A
    double **U;           //
    double *b;            // vetor b tal que  LUx = b,
    double *y;            // vetor y tal que Ux = y e Ly= b
    unsigned int *trocas; //Armazena para cada posição, onde se encontra o valor original para o mesmo
} FatoracaoLU;



//---Alocaçao e desalocação de memória
// aloca matriz quadrada
double **alocaMatrizQ(int n);
// libera matriz quadrada
void liberaMatrizQ(double **M, int n);

// Aloca fatoração LU
FatoracaoLU *alocaFatoracaoLU(unsigned int n);
// Libera fatoração LU
void liberaFatoracaoLU(FatoracaoLU *LU);

//---Leitura e impressão de sistemas lineares
// Leitura dos inputs
FatoracaoLU *lerMatriz();
// Exibe estrutura de fatoração LU
void printFatoracaoLU(FatoracaoLU *lu, bool soMatriz);
// Exibe resultado final no padão especificado
void printResultado(FatoracaoLU *LU, double **Transp_INV, metricas *m);

//---Gerenciamento do algoritmo e funções auxiliares
// Troca duas linhas de um FatoracaoLU.A, armazenado a troca executada
void trocaLinha(FatoracaoLU *LU, int A, int B);
// Reverte todas as trocas de linha efetivadas
void reverteTrocaLinha(FatoracaoLU *lu);

//---Funções objetivo do projeto
//Resolução de sistemas diagonais
void resolveSisTriangular(double **ST, double *x, double *b, int n, bool superior);
// Calcula Inversa de uma matriz (armazenando resultado como transposta)
void calculaInversa(FatoracaoLU *LU, double **Transp_INV, metricas *m, bool pivota);
// Triangulação de uma matriz A em L*U
int triangulaLU(FatoracaoLU *LU, bool pivota);

int calculaY(FatoracaoLU *LU);
int calculaX(FatoracaoLU *LU, double *X);

// Retorna a normaL2 do resíduo. Parâmetro 'res' deve ter o resíduo.
double normaL2Inversa(FatoracaoLU *LU, double **Transp_INV);

#endif // __FAT_LU_H__

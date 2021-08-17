#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "calculaInversa.h"
#ifndef __FAT_LU_H_OTM__
#define __FAT_LU_H_OTM__

// Estrutura para armazenar uma matriz A, decompola em LU  a fim de calcular a matriz inversa
typedef struct
{
    unsigned int n; // Ordem da matriz
    double **A;     // matrix A
    double **LU;    // L*U =A
    // double **U;           //
    double *b;            // vetor b tal que  LUx = b,
    double *y;            // vetor y tal que Ux = y e Ly= b
    int *trocas; //Armazena para cada posição, onde se encontra o valor original para o mesmo
} FatoracaoLUOtm;

//---Alocaçao e desalocação de memória
// aloca matriz quadrada otimizada
double **alocaMatrizQOtm(int n);
// libera matriz quadrada
void liberaMatrizQOtm(double **M);

// Aloca fatoração LU
FatoracaoLUOtm *alocaFatoracaoLUOtm(unsigned int n);
// Libera fatoração LU
void liberaFatoracaoLUOtm(FatoracaoLUOtm *LU);



//---Leitura e impressão de sistemas lineares
// Leitura dos inputs
FatoracaoLUOtm *lerMatrizOtm();
FatoracaoLUOtm* cp2otm(FatoracaoLU *lu); 
// Exibe estrutura de fatoração LU
void printFatoracaoLUOtm(FatoracaoLUOtm *lu, bool soMatriz);
// Exibe resultado final no padão especificado
void printResultadoOtm(FatoracaoLUOtm *LU, double **Transp_INV, metricas *m);

//---Gerenciamento do algoritmo e funções auxiliares
// Troca duas linhas de um FatoracaoLUOtm.A, armazenado a troca executada
void trocaLinhaLogica(FatoracaoLUOtm *LU, int A, int B);
// Reverte todas as trocas de linha efetivadas
void reverteTrocaLinhaLogica(FatoracaoLUOtm *lu);

//---Funções objetivo do projeto
//Resolução de sistemas diagonais
void resolveSisTriangular(double **ST, double *x, double *b, int n, bool superior);
// Calcula Inversa de uma matriz (armazenando resultado como transposta)
void calculaInversaOtm(FatoracaoLUOtm *LU, double **Transp_INV, metricas *m, bool pivota);
// Triangulação de uma matriz A em L*U
int triangulaLUOtm(FatoracaoLUOtm *LU, bool pivota);

int calculaYOtm(FatoracaoLUOtm *LU);
int calculaXOtm(FatoracaoLUOtm *LU, double *X);

// Retorna a normaL2 do resíduo. Parâmetro 'res' deve ter o resíduo.
double normaL2InversaOtm(FatoracaoLUOtm *LU, double **Transp_INV);

#endif // __FAT_LU_H_OTM__

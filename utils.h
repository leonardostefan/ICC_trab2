#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#define false 0
#define true !false
typedef char bool;

// Estrutura para armazenar os resultados das metricas utilizadas
typedef struct
{
    double timeTotal; //Tempo total de execução
    double timeTri;   //tempo da triangulação
    double timeY;     //tempo do calculo de y
    double timeX;     //tempo do calculo de x
    double normaL2;   //resultado do calculo da normaL2
} metricas;

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/
void printMatrizQ(double **M, int n);
void printVector(double *x, int n);

int encontraMax(double **A, unsigned int j, unsigned n);

double timestamp(void);

#endif // __UTILS_H__

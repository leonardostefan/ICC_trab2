
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "calculaInversa.h"
#ifndef __POLINOMIO__
#define __POLINOMIO__

typedef struct
{
    int n;
    int m;
    double *x;  //n valores tabelados
    double **f; // m funções tabeladas *n
} inputPolinomial;

typedef struct
{
    int n;
    double *x;    //n valores tabelados
    double **odd; // matriz de Operador de Diferenças Divididas, onde odd[i][j]== f[Xj+0,..,Xj+i], i sendo a ordem desejada do polinomio, j o indice do valor tabelado
} interPolNewton;


void calculaInterPolSL(double *x, double *y, int n, double *coef, bool pivota);


interPolNewton *alocaInterPolNewton(int n, double *x, double *fx);
inputPolinomial *alocaInputPol(int m, int n);

inputPolinomial *lerFuncoes();

void completa_interPolNewton(interPolNewton *ip, double *d);
double verifica_interPolNewton(interPolNewton *ip, double *d);

double *calculaTermosMinimosQuadrados(double *x, int n, int grau);
int montaLUMinimosQuadrados(double *termos, FatoracaoLU *lu, int grau ,bool pivota);
int calculaPolinomioMinimosQuadrados(double *x,int n, FatoracaoLU *lu, double *y, double *coef, int grau ,bool pivota);

#endif // __POLINOMIO__

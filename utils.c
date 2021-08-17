#include "utils.h"
#include <math.h>

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

/*!
  \brief Imprime uma matriz quadrada de doubles de ordem n;
  \param M matriz 
  \param n ordem da matriz 
  \return sem retorno;
  */
void printMatrizQ(double **M, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%.2lf\t", (M)[i][j]);
    }
    printf("\n");
  }
}

/*!
  \brief Encontra maior valor(absoluto) na coluna a partir da linha j

  \param A Matriz quadrada de tamanho 'n'
  \param j linha de inicio 
  \param n tamanho da matriz

  \return indice da linha com o maior valor
*/
int encontraMax(double **A, unsigned int j, unsigned n)
{
  double maior = -INFINITY;
  double current = -INFINITY;
  unsigned idMax = 0;
  for (int i = j; i < n; i++)
  {
    current = A[i][j] > 0 ? A[i][j] : -A[i][j];
    if (maior < current)
    {
      maior = current;
      idMax = i;
    }
  }
  return idMax;
}

void printVector(double *x, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%.20lf ", x[i]);
  }
  printf("\n");
}
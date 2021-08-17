#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "calculaInversaOtm.h"

#include "calculaInversa.h"
#define UNROLL false

#define UNROLL_SIZE 8
/*!
  \brief Faz invesão posição d acessos das linhas A e B linhas de um FatoraçãoLUOtm para as matrizes A e U, armazenando a troca no vetor trocas 
   OBS: Muda apenas o acesso do ponteiro M[i], o posicionamento em memória permanece o mesmo M[0][i*n]
  \param lu  Fatoração LU instanciada
  \param x indice da linha 
  \param y indice da linha 
  \return Sem retorno;
*/
void 
trocaLinhaLogica(FatoracaoLUOtm *lu, int x, int y)
{
    // Inverte as linhas na matriz original
    double *auxA = lu->A[x];
    lu->A[x] = lu->A[y];
    lu->A[y] = auxA;
    // Inverte e U
    double *auxU = lu->LU[x];
    lu->LU[x] = lu->LU[y];
    lu->LU[y] = auxU;

    // Armazena "histórico" de trocas
    double auxI = lu->trocas[x];
    lu->trocas[x] = lu->trocas[y];
    lu->trocas[y] = auxI;

    // Não troca linhas de L pois ainda não esta preenchida (é preenchido já trocado)
    //Não troca linha em y e em b pois sera feito em tempo de execução
}
/*!
  \brief Desfaz a todas as inversões realizadas (O(n)) na FatoraçãoLU, afeta somente as matrizes A e U, reiniciando vetor trocas.
  \param lu  Fatoração LU instanciada
  \return Sem retorno;
*/
void reverteTrocaLinhaLogica(FatoracaoLUOtm *lu)
{
    // O seguinte código aparenta ser O(n^2),porém é O(n) uma vez que para cada execução do while é uma "execução a menos" no for
    int i = 0;
    int j = 0;
    for (i = 0; i < lu->n; i++)
    {
        while (j != i)
        {
            j = lu->trocas[i];
            trocaLinhaLogica(lu, i, j);
        }
    }
    // Ignora matrizes L e U pois não sao mais necessárias se esta sendo realizado a destroca;
}

/*!
  \brief Alocaçao de memória  FatoracaoLUOtm, realiza o alocamento de cada matriz no estilo linha, calculando e armazenado os endereços de memória ponteiro de ponteiros;

  \param n tamanho/ordem da matriz quadrada

  \return ponteiro para LU.
  */
FatoracaoLUOtm *alocaFatoracaoLUOtm(unsigned int n)
{
    FatoracaoLUOtm *LU = calloc(1, sizeof(FatoracaoLUOtm));
    LU->n = n;
    LU->y = calloc(n, sizeof(double));
    LU->b = calloc(n, sizeof(double));

    LU->A = calloc(n, sizeof(double *));
    LU->A[0] = calloc(n * n, sizeof(double));

    LU->LU = calloc(n, sizeof(double *));
    LU->LU[0] = calloc(n * n, sizeof(double));

    LU->trocas = calloc(n, sizeof(int));

    for (int i = 1; i < n; i++)
    {
        LU->trocas[i] = i;
        LU->A[i] = &(LU->A[0][i * n]);
        LU->LU[i] = &(LU->LU[0][i * n]);
    }
    return LU;
}
/*!
  \brief Alocaçao de memória  matriz double

  \param n tamanho/ordem da matriz quadrada

  \return ponteiro para matriz.
  */
double **alocaMatrizQOtm(int n)
{
    double **M = calloc(n, sizeof(double *));
    M[0] = calloc(n * n, sizeof(double));
    for (int i = 1; i < n; i++)
        M[i] = &(M[0][i * n]);
    return M;
}
/*!
  \brief Liberaçao de memória matriz quadrada

  \param M linear SL
  \param n tamanho/ordem da matriz
  */
void liberaMatrizQOtm(double **M)
{
    free(M[0]);
    free(M);
}
/*!
  \brief Liberaçao de memória FatoracaoLUOtm

  \param LU linear SL
  */
void liberaFatoracaoLUOtm(FatoracaoLUOtm *LU)
{
    free(LU->y);
    free(LU->b);
    free(LU->trocas);

    liberaMatrizQOtm(LU->LU);
    liberaMatrizQOtm(LU->A);
    free(LU);
    return;
}
/*!
  \brief Leitura da matriz a partir de Entrada padrão (stdin).

  \return FatoracaoLUOtm instanciada, com a matriz lida em LU->A porem ainda não triangulada. NULL se houve erro (leitura ou alocação)
  */
FatoracaoLUOtm *lerMatrizOtm()
{
    int n = 0;
    if (scanf("%d\n", &(n)) == EOF)
    {
        return NULL;
    }
    FatoracaoLUOtm *lu = alocaFatoracaoLUOtm(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (scanf("%lf ", &((lu->A)[i][j])) == EOF)
            {

                printf("\e[32mERRO:\e[39m Input mal formatado. Esperando valor na matriz");
                return NULL;
            }
            else
            {
                // Realiza a copia de A em U previamente para garantir cache hit e não ser necessãrio a mesma operação durante a triangulação
                (lu->LU)[i][j] = (lu->A)[i][j];
            }
        }
    }
    return lu;
}
// Copia FatoracaoLU não triangulada em uma FatoracaoLUOtm
FatoracaoLUOtm *cp2otm(FatoracaoLU *lu)
{
    int n = lu->n;
    FatoracaoLUOtm *otm = alocaFatoracaoLUOtm(n);
    otm->n = n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            otm->A[i][j] = lu->A[i][j];
            otm->LU[i][j] = lu->A[i][j];
            // otm->LU[i][j] = i < j ? lu->L[i][j] : lu->U[i][j];
        }
        otm->trocas[i] = lu->trocas[i];
    }
    return otm;
}

/*!
  \brief Imprime uma matriz quadrada de doubles de ordem n;
  \param lu FatoracaoLUOtm a ser exibida
  \param soMatriz se verdadeiro, imprime somente L U e A, não exibindo y, b  e trocas
  \return sem retorno;
  */
void printFatoracaoLUOtm(FatoracaoLUOtm *lu, bool soMatriz)
{
    printf("\e[33mFatoração LU A:\n\e[39m");
    int n = lu->n;
    printf("A:\n");
    printMatrizQ(lu->A, n);
    printf("LU:\n");
    // printMatrizQ(lu->L, n);
    // printf("U:\n");
    printMatrizQ(lu->LU, n);
    if (!soMatriz)
    {
        printf("y:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%.3lf ", lu->y[i]);
        }
        printf("\nb:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%.3lf ", lu->b[i]);
        }
        printf("\ntrocas:\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", lu->trocas[i]);
        }
        printf("\n");
    }
    return;
}

/*!
    \brief A partir de uma instancia de FatoracaoLUOtm, não triangulada, realiza a triangulação, e calcula a matriz transposta da inversa de LU->A, calculando tempo de execução e normaL2
    \param LU FatoracaoLUOtm com a matriz 
    \param Transp_INV Matriz de double onde sera armazenada a tranposta da inversa
    \param m amazenara as metricas calculadas;
    \param pivota se verdadeiro, realiza pivoteamento
    \return Sem retorno
*/
void calculaInversaOtm(FatoracaoLUOtm *LU, double **Transp_INV, metricas *m, bool pivota)
{
    double triangTime = 0, yTime = 0, xTime = 0;
    triangTime += triangulaLUOtm(LU, pivota);
    int n = LU->n;
    // para Coluna da Inversa (cada linha da inversa tranposta)
    for (int i = 0; i < n; i++)
    {
        // Inicializa vetor B
        for (int j = 0; j < n; j++)
            // não faz parte da diagonal = 0
            LU->b[j] = 0;
        // faz parte da diagonal = 1
        LU->b[i] = 1;

        yTime += calculaYOtm(LU);
        // Para facilitar no gerenciamento da memória e velocidade de acesso, será calculado a tranposta da matriz inversa
        xTime += calculaXOtm(LU, Transp_INV[i]);
    }

    if (pivota)
    {
        // X foi calculado com as linhas trocadas, agora é reposicionado para que retornar o valor correto;
        // LU->trocas[i] informa a posição em que X[i] deveria estar, O(n)

        double **xCopy = calloc(n, sizeof(double *));
        int *t = LU->trocas;
        for (int i = 0; i < n; i++)
            xCopy[t[i]] = Transp_INV[i];
        // Repassa para vetor X original
        for (int i = 0; i < n; i++)
            Transp_INV[i] = xCopy[i];
        // Revere troca de linhas em A e U
        reverteTrocaLinhaLogica(LU);
    }
    m->timeTotal = triangTime + yTime + xTime;
    m->timeTri = triangTime;
    m->timeY = yTime / n;
    m->timeX = xTime / n;
    m->normaL2 = normaL2InversaOtm(LU, Transp_INV);
}
/*!
    \brief sub processos do calculo da inversa, realiza a triangulação de lu
    \param LU FatoracaoLUOtm com a matriz a ser triangulada
    \param pivota se verdadeiro, realiza pivoteamento
    \return tempo de execução
*/
int triangulaLUOtm(FatoracaoLUOtm *lu, bool pivota)
{
    double initTime = timestamp();
    int n = lu->n;

    // double **A = lu->A;
    // double **LU = lu->LU;

    for (int i = 0; i < n; ++i)
    {
        // printFatoracaoLUOtm(lu, true);

        if (pivota)
        {
            unsigned int pivo = encontraMax(lu->LU, i, n);
            if (i != pivo)
                trocaLinhaLogica(lu, i, pivo);
        }

        if (lu->LU[i][i] != 0)
        {
            int k;
            double mult[UNROLL_SIZE];
            double LUii;
            for (k = i + 1; k+(UNROLL_SIZE-1) <  n; k += UNROLL_SIZE)
            {
                LUii = lu->LU[i][i];
                mult[0] = lu->LU[k + 0][i] / LUii;
                mult[1] = lu->LU[k + 1][i] / LUii;
                mult[2] = lu->LU[k + 2][i] / LUii;
                mult[3] = lu->LU[k + 3][i] / LUii;
                mult[4] = lu->LU[k + 4][i] / LUii;
                mult[5] = lu->LU[k + 5][i] / LUii;
                mult[6] = lu->LU[k + 6][i] / LUii;
                mult[7] = lu->LU[k + 7][i] / LUii;

                lu->LU[k + 0][i] = mult[0];
                lu->LU[k + 1][i] = mult[1];
                lu->LU[k + 1][i] = mult[1];
                lu->LU[k + 2][i] = mult[2];
                lu->LU[k + 3][i] = mult[3];
                lu->LU[k + 4][i] = mult[4];
                lu->LU[k + 5][i] = mult[5];
                lu->LU[k + 6][i] = mult[6];
                lu->LU[k + 7][i] = mult[7];

                int j = i + 1;
                {
                    for (j = i + 1; j < n; j++)
                    {
                        lu->LU[k + 0][j] -= lu->LU[i][j] * mult[0];
                        lu->LU[k + 1][j] -= lu->LU[i][j] * mult[1];
                        lu->LU[k + 2][j] -= lu->LU[i][j] * mult[2];
                        lu->LU[k + 3][j] -= lu->LU[i][j] * mult[3];
                        lu->LU[k + 4][j] -= lu->LU[i][j] * mult[4];
                        lu->LU[k + 5][j] -= lu->LU[i][j] * mult[5];
                        lu->LU[k + 6][j] -= lu->LU[i][j] * mult[6];
                        lu->LU[k + 7][j] -= lu->LU[i][j] * mult[7];
                    }
                }
            for (; k < n; ++k)
            {
                mult[0] = lu->LU[k][i] / lu->LU[i][i];
                lu->LU[k][i] = mult[0];

                int j = i + 1;
                {
                    for (j = i + 1; j < n; j++)
                    {
                        lu->LU[k][j] -= lu->LU[i][j] * mult[0];
                    }
                }
            }
            }
        }
    }

    return timestamp() - initTime;
}
/*!
    \brief Sub processos do calculo da inversa, descobre Y tal que Ly = b, b já deve estar inicializado para a execução
    \param LU FatoracaoLUOtm com a matriz já triangulada e b inicializado;
    \return tempo de execução
*/
int calculaYOtm(FatoracaoLUOtm *LU)
{
    double initTime = timestamp();

    // Descobre y

    double **ST = LU->LU;
    double *x = LU->y;
    double *b = LU->b;
    int n = LU->n;

    for (int i = 0; i < n; i++)
    {

        x[i] = b[i];
        // Calcula apenas nas pozições abaixo da diagona principal da matriz (diagonal não inclusa)
        for (int j = 0; j < i; j++)
        {
            x[i] -= x[j] * ST[i][j];
        }
        // Assume que a matriz L separadamente
    }

    // Mantem o resultado armazenado em Y na posição trocada
    return timestamp() - initTime;
}
/*!
    \brief Sub processos do calculo da inversa, descobre X tal que Ux = y, y já deve estar calculado para a execução
    \param LU FatoracaoLUOtm com a matriz já triangulada e y calculado;
    \param X vetor resultante X (coluna calculadada matriz inversa/ linha da matriz inversa transposta)
    \return tempo de execução
*/
int calculaXOtm(FatoracaoLUOtm *LU, double *X)
{
    double initTime = timestamp();
    double **ST = LU->LU;
    double *b = LU->y;
    int n = LU->n;

    for (int i = n - 1; i >= 0; i--)
    {
        if (ST[i][i] != 0)
        {
            X[i] = b[i];
            // Calcula apenas nas pozições não zeradas da matriz

            for (int j = n - 1; j > i; j--)
            {
                X[i] -= X[j] * ST[i][j];
            }
            X[i] = X[i] / ST[i][i];
        }
        else
            // TODO: Retornar erro
            X[i] = 0;
    }

    return timestamp() - initTime;
}

/*!
  \brief Essa função calcula a norma L2 do resíduo da multiplicação de uma matriz pela sua inversa (A*A⁻¹). Esta sendo utilizado apeas o valor da diagonal da identidade pois é mais rápido e diminui a chance de ocorrer erros de ponto flutuante no próprio calculo da normaL2;
  \param LU Ponteiro para FatoracaoLUOtm com A armazenado (e sem linhas trocadas)
  \param Transp_INV Matriz Transposta da inversa de LU->A
  \return Norma L2 do resíduo.
*/
double normaL2InversaOtm(FatoracaoLUOtm *LU, double **Transp_INV)
{

    int res = 0;
    double bxp = 0;
    double prod = 0;
    //O Calculo do residuo esta sendo com a multiplicação das matrizes A x A⁻¹
    //Esta sendo utilizado apeas o valor da diagonal da identidade pois é mais rápido e diminui a chance de ocorrer erros de pondo flutuante no próprio calculo de erro;
    for (int i = 0; i < LU->n; i++, prod = 0)
    {
        //Como estamos utilizando a transposta da Inversa, o acesso a memória é mais rápido e é feito a multiplicação de Linha*Linha  ao invés de Linha*Coluna
        for (int j = 0; j < LU->n; j++)
        {
            prod += LU->A[i][j] * Transp_INV[i][j];
        }
        bxp = 1 - prod;
        (res) += bxp * bxp;
    }
    return (sqrtf(res));
}

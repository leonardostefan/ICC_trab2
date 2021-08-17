#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "calculaInversa.h"

/*!
  \brief Faz invesão posição das linhas A e B linhas de um FatoraçãoLU para as matrizes A e U, armazenando a troca no vetor trocas
  \param lu  Fatoração LU instanciada
  \param x indice da linha 
  \param y indice da linha 
  \return Sem retorno;
*/
void trocaLinha(FatoracaoLU *lu, int x, int y)
{
    // Inverte as linhas na matriz original
    double *auxA = lu->A[x];
    lu->A[x] = lu->A[y];
    lu->A[y] = auxA;
    // Inverte e U
    double *auxU = lu->U[x];
    lu->U[x] = lu->U[y];
    lu->U[y] = auxU;

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
void reverteTrocaLinha(FatoracaoLU *lu)
{
    // O seguinte código aparenta ser O(n^2),porém é O(n) uma vez que para cada execução do while é uma "execução a menos" no for
    int i = 0;
    int j = 0;
    for (i = 0; i < lu->n; i++)
    {
        while (j != i)
        {
            j = lu->trocas[i];
            trocaLinha(lu, i, j);
        }
    }
    // Ignora matrizes L e U pois não sao mais necessárias se esta sendo realizado a destroca;
}

/*!
  \brief Alocaçao de memória  FatoracaoLU

  \param n tamanho/ordem da matriz quadrada

  \return ponteiro para LU.
  */
FatoracaoLU *alocaFatoracaoLU(unsigned int n)
{
    FatoracaoLU *LU = calloc(1, sizeof(FatoracaoLU));

    LU->A = calloc(n, sizeof(double *));
    LU->n = n;
    LU->L = calloc(n, sizeof(double *));
    LU->U = calloc(n, sizeof(double *));
    LU->y = calloc(n, sizeof(double));
    LU->b = calloc(n, sizeof(double));
    LU->trocas = calloc(n, sizeof(unsigned int));

    for (int i = 0; i < n; i++)
    {
        LU->L[i] = calloc(n, sizeof(double));
        LU->U[i] = calloc(n, sizeof(double));
        LU->A[i] = calloc(n, sizeof(double));

        //Inicia cada posição com o proprio valor indicando que é a posição original da linha
        LU->trocas[i] = i;
    }
    return LU;
}
/*!
  \brief Alocaçao de memória  matriz double

  \param n tamanho/ordem da matriz quadrada

  \return ponteiro para matriz.
  */
double **alocaMatrizQ(int n)
{
    double **M = calloc(n, sizeof(double *));
    for (int i = 0; i < n; i++)
        M[i] = calloc(n, sizeof(double));
    return M;
}
/*!
  \brief Liberaçao de memória matriz quadrada

  \param M linear SL
  \param n tamanho/ordem da matriz
  */
void liberaMatrizQ(double **M, int n)
{
    for (int i = n - 1; i >= 0; i--)
        free(M[i]);
    free(M);
}
/*!
  \brief Liberaçao de memória FatoracaoLU

  \param LU linear SL
  */
void liberaFatoracaoLU(FatoracaoLU *LU)
{
    free(LU->y);
    free(LU->b);
    free(LU->trocas);

    for (int i = LU->n - 1; i >= 0; i--)
    {
        free(LU->L[i]);
        free(LU->U[i]);
    }
    free(LU);
    return;
}
/*!
  \brief Leitura da matriz a partir de Entrada padrão (stdin).

  \return FatoracaoLU instanciada, com a matriz lida em LU->A porem ainda não triangulada. NULL se houve erro (leitura ou alocação)
  */
FatoracaoLU *lerMatriz()
{
    int n = 0;
    if (scanf("%d\n", &(n)) == EOF)
    {
        return NULL;
    }
    FatoracaoLU *lu = alocaFatoracaoLU(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (scanf("%lf ", &((lu->A)[i][j])) == EOF)
            {

                printf("\e[32mERRO:\e[39m Input mal formatado. Esperando valor na matriz");
                return NULL;
            }
        }
    }
    return lu;
}
/*!
  \brief Imprime uma matriz quadrada de doubles de ordem n;
  \param lu FatoracaoLU a ser exibida 
  \param soMatriz se verdadeiro, imprime somente L U e A, não exibindo y, b  e trocas
  \return sem retorno;
  */
void printFatoracaoLU(FatoracaoLU *lu, bool soMatriz)
{
    printf("\e[33mFatoração LU A:\n\e[39m");
    int n = lu->n;
    printf("A:\n");
    printMatrizQ(lu->A, n);
    printf("L:\n");
    printMatrizQ(lu->L, n);
    printf("U:\n");
    printMatrizQ(lu->U, n);
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
  \brief Imprime resultado final especificado
<ordem matriz>
<Matriz de Entrada>
#
<Matriz Inversa>
###########
# Tempo Triangularização: <tempo para a triangularização, em milisegundos>
# Tempo cálculo de Y: <tempo médio do cálculo de 'y' em Ly = b, em milisegundos>
# Tempo cálculo de X: <tempo médio do cálculo de 'x' em Ux = y, em milisegundos>
# Norma L2 do Residuo: <valores das N normas L2 dos resíduos>
###########
  \param LU FatoracaoLU a calculada
  \param Transp_INV Matriz inversa transposta calculada
  \param m metricas calculadas
  \return sem retorno;
  */
void printResultado(FatoracaoLU *LU, double **Transp_INV, metricas *m)
{

    // <ordem matriz>
    printf("%d\n", LU->n);
    // <Matriz de Entrada>
    for (int i = 0; i < LU->n; i++)
    {
        for (int j = 0; j < LU->n; j++)
        {
            printf("%.2lf\t", (LU->A)[i][j]);
        }
        printf("\n");
    }
    //
    printf("#\n");
    // <Matriz Inversa>
    for (int j = 0; j < LU->n; j++) //Como foi calculado a tranposta, é invertido o loop [i][j]
    {
        for (int i = 0; i < LU->n; i++)
        {
            printf("%.3lf\t", (Transp_INV)[i][j]);
        }
        printf("\n");
    }
    //
    printf("###########\n");
    printf("# Tempo Triangularização: %.4lf\n", m->timeTri);
    printf("# Tempo cálculo de Y: %.4lf\n", m->timeY);
    printf("# Tempo cálculo de X: %.4lf\n", m->timeX);
    printf("# Tempo Total: %.4lf\n", m->timeTotal);
    printf("# Norma L2 do Residuo: %.10lf\n", m->normaL2);

    printf("\e[92m###########\e[39m\n");
}
/*!
    \brief A partir de uma instancia de FatoracaoLU, não triangulada, realiza a triangulação, e calcula a matriz transposta da inversa de LU->A, calculando tempo de execução e normaL2
    \param LU FatoracaoLU com a matriz 
    \param Transp_INV Matriz de double onde sera armazenada a tranposta da inversa
    \param m amazenara as metricas calculadas;
    \param pivota se verdadeiro, realiza pivoteamento
    \return Sem retorno
*/
void calculaInversa(FatoracaoLU *LU, double **Transp_INV, metricas *m, bool pivota)
{
    double triangTime = 0, yTime = 0, xTime = 0;
    triangTime += triangulaLU(LU, pivota);
    int n = LU->n;

    // printFatoracaoLU(LU, true);
    // para Coluna da Inversa (cada linha da inversa tranposta)
    for (int i = 0; i < n; i++)
    {
        // Inicializa vetor B
        for (int j = 0; j < n; j++)
            // não faz parte da diagonal = 0
            LU->b[j] = 0;
        // faz parte da diagonal = 1
        LU->b[i] = 1;

        yTime += calculaY(LU);
        // Para facilitar no gerenciamento da memória e velocidade de acesso, será calculado a tranposta da matriz inversa
        xTime += calculaX(LU, Transp_INV[i]);
    }

    if (pivota)
    {
        // X foi calculado com as linhas trocadas, agora é reposicionado para que retornar o valor correto;
        // LU->trocas[i] informa a posição em que X[i] deveria estar, O(n)

        double **xCopy = calloc(n, sizeof(double *));
        unsigned int *t = LU->trocas;
        for (int i = 0; i < n; i++)
            xCopy[t[i]] = Transp_INV[i];
        // Repassa para vetor X original
        for (int i = 0; i < n; i++)
            Transp_INV[i] = xCopy[i];
        // Revere troca de linhas em A e U
        reverteTrocaLinha(LU);
    }
    m->timeTotal = triangTime + yTime + xTime;
    m->timeTri = triangTime;
    m->timeY = yTime / n;
    m->timeX = xTime / n;
    m->normaL2 = normaL2Inversa(LU, Transp_INV);
}
/*!
    \brief Sub processos do calculo da inversa, realiza a triangulação de LU
    \param LU FatoracaoLU com a matriz a ser triangulada
    \param pivota se verdadeiro, realiza pivoteamento
    \return tempo de execução
*/
int triangulaLU(FatoracaoLU *lu, bool pivota)
{
    double initTime = timestamp();
    int n = lu->n;

    double **A = lu->A;
    double **U = lu->U;

    // Coia A em U;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            lu->U[i][j] = A[i][j];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (pivota)
        {
            unsigned int pivo = encontraMax(A, i, n);
            if (i != pivo)
                trocaLinha(lu, i, pivo);
        }
        lu->L[i][i] = 1;
        if (U[i][i] != 0)
        {
            for (int k = i + 1; k < n; ++k)
            {
                double mult = U[k][i] / U[i][i];
                lu->L[k][i] = mult;
                U[k][i] = 0;
                for (int j = i + 1; j < n; ++j)
                    U[k][j] -= U[i][j] * mult;
                // b[k] -= b[i] * mult;
            }
        }
    }

    return timestamp() - initTime;
}
/*!
    \brief Sub processos do calculo da inversa, realiza a triangulação de LU
    \param ST matris com o sistema triangular 
    \param x variaveis
    \param b termo independente
    \param n tamanho/ordem da matriz
    \param superior se verdadeiro calcula para matriz triangular superior, se falso para matriz triangular inferior
    \return sem retorno
*/
void resolveSisTriangular(double **ST, double *x, double *b, int n, bool superior)
// Calcula no formato ST*x=b
{
    if (superior) //Calcula caso matriz tringular superior
        for (int i = n - 1; i >= 0; i--)
        {
            if (ST[i][i] != 0)
            {
                x[i] = b[i];
                // Calcula apenas nas pozições não zeradas da matriz
                for (int j = n - 1; j > i; j--)
                {
                    x[i] -= x[j] * ST[i][j];
                }
                x[i] = x[i] / ST[i][i];
            }
            else
                x[i] = 0;
        }
    else //Calcula caso matriz tringular inferior
        for (int i = 0; i < n; i++)
        {
            if (ST[i][i] != 0)
            {
                x[i] = b[i];
                // Calcula apenas nas pozições não zeradas da matriz
                for (int j = 0; j < i; j++)
                {
                    x[i] -= x[j] * ST[i][j];
                }
                x[i] = x[i] / ST[i][i];
            }
            else
                x[i] = 0;
        }
}
/*!
    \brief Sub processos do calculo da inversa, descobre Y tal que Ly = b, b já deve estar inicializado para a execução
    \param LU FatoracaoLU com a matriz já triangulada e b inicializado;
    \return tempo de execução
*/
int calculaY(FatoracaoLU *LU)
{
    double initTime = timestamp();

    // Descobre y
    resolveSisTriangular(LU->L, LU->y, LU->b, LU->n, false);

    // Mantem o resultado armazenado em Y na posição trocada
    return timestamp() - initTime;
}
/*!
    \brief Sub processos do calculo da inversa, descobre X tal que Ux = y, y já deve estar calculado para a execução
    \param LU FatoracaoLU com a matriz já triangulada e y calculado;
    \param X vetor resultante X (coluna calculadada matriz inversa/ linha da matriz inversa transposta)
    \return tempo de execução
*/
int calculaX(FatoracaoLU *LU, double *X)
{
    double initTime = timestamp();
    int n = LU->n;

    resolveSisTriangular(LU->U, X, LU->y, n, true);

    return timestamp() - initTime;
}

/*!
  \brief Essa função calcula a norma L2 do resíduo da multiplicação de uma matriz pela sua inversa (A*A⁻¹). Esta sendo utilizado apeas o valor da diagonal da identidade pois é mais rápido e diminui a chance de ocorrer erros de ponto flutuante no próprio calculo da normaL2;
  \param LU Ponteiro para FatoracaoLU com A armazenado (e sem linhas trocadas)
  \param Transp_INV Matriz Transposta da inversa de LU->A
  \return Norma L2 do resíduo.
*/
double normaL2Inversa(FatoracaoLU *LU, double **Transp_INV)
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

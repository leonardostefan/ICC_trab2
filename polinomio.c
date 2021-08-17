#include "polinomio.h"
#include "calculaInversa.h"

/*!
    \brief Calcula coeficientes da interpolação polinomial de F[x]=y de ordem n-1
    \param x Vetor de valores tabelados de x
    \param y Valores de f[x] conhecidos
    \param n Quantidade de x tabelados
    \param coef vetor de resposta com os coeficientes
    \param pivota souluciona SL utilizando pivotamento parcial 
    \return sem retorno
*/
void calculaInterPolSL(double *x, double *y, int n, double *coef, bool pivota)
{
    FatoracaoLU *lu = alocaFatoracaoLU(n);
    double xi = 0;   // valor de X indice i
    double xPow = 1; // x^j

    // TODO: olhar valores de X e tentar montar a matriz com um pseudo pivotamento total
    for (int i = 0; i < n; i++, xPow = 1)
    {
        xi = x[i];
        for (int j = 0; j < n; j++, xPow *= xi)
        {
            lu->A[i][j] = xPow;
        }
    }
    triangulaLU(lu, pivota);
    for (int i = 0; i < n; i++)
    {
        lu->b[i] = y[i];
    }
    calculaY(lu);
    calculaX(lu, coef);
    liberaFatoracaoLU(lu);
}

/*!
    \brief Aloca estrutura para calcular coeficiente do Interpolador Polinomial de Newtonu
    \param n Quantidade de x tabelados
    \param x Vetor de valores tabelados de x
    \param y Valores de f[x] conhecidos
    \return Instancia da estrutura interPolNewton 
*/
interPolNewton *alocaInterPolNewton(int n, double *x, double *y)
{
    interPolNewton *ip = calloc(1, sizeof(interPolNewton));

    ip->n = n;
    ip->x = x;

    //A matriz de Operador de Diferenças Divididas (odd) é representada em odd[i][j] = f[Xj..Xi+j]  onde i é a ordem e j o indice inicial da ordem
    ip->odd = calloc(n, sizeof(double *));
    // A primeira linha da odd é o próprio valor já tabelado  F[Xi] === F(Xi) === y[i]
    ip->odd[0] = y;
    // Tamanho Do restante da matriz que precisa ser calculada
    int nInf = n - 1;

    // TODO: verificar se alocar triangular melhora no desempenho
    ip->odd[1] = calloc(nInf * nInf, sizeof(double));
    for (int i = 0; i < nInf; i++)
    {
        ip->odd[i + 1] = &((ip->odd)[1][i * nInf]);
    }
    return ip;
}

/*!
    \brief Calcula coeficientes da interpolação polinomial pelo metodo de Newton 
    \param ip Estrutura de dados do interpolador com x e primeira ordem calculada;
    \param d vetor de coeficientes resultates (deve estar instanciado)
    \return sem retorno
*/
void completa_interPolNewton(interPolNewton *ip, double *d)
{
    double **odd = ip->odd;
    double *x = ip->x;

    for (int i = 1; i < ip->n; i++)
    {
        for (int j = 0; j < ip->n - i; j++)
        {
            // F[Xj..Xj+i] === (F(Xj+1..Xj+i)-F(Xj+1..Xj+i-1))/ (Xj+i - Xj)
            odd[i][j] = (odd[i - 1][j + 1] - odd[i - 1][j]) / (x[j + i] - x[j]);
        }
    }
    // repassa valores dos coefientes calculados para vetor de resultante
    for (int i = 0; i < ip->n; i++)
    {
        d[i] = odd[i][0];
    }
}

/*!
    \brief Calcula coeficientes da interpolação polinomial pelo metodo de Newton 
    \param ip Estrutura de dados do interpolador com x e primeira ordem calculada;
    \param d coeficientes resultates
    \return sem retorno
*/
inputPolinomial *alocaInputPol(int m, int n)
{
    inputPolinomial *pols = calloc(1, sizeof(inputPolinomial));
    double *x = calloc(n, sizeof(double));
    double **f = calloc(m, sizeof(double *));
    f[0] = calloc(m * n, sizeof(double));

    for (int i = 0; i < m; i++)
    {
        f[i] = &(f[0][i * n]);
    }

    pols->n = n;
    pols->m = m;
    pols->f = f;
    pols->x = x;
    return pols;
}

/*!
  \brief Leitura da matriz a partir de Entrada padrão (stdin).

  \return Estrutura inputPolinomial instanciada, com valores de x amazenados e matriz de Fi[x]
  */
inputPolinomial *lerFuncoes()
{
    int n, m;
    if (scanf("%d %d\n", &(n), &(m)) == EOF)
    {
        return NULL;
    }

    inputPolinomial *pols = alocaInputPol(m, n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%lf ", &(pols->x[i])) == EOF)
        {
            return NULL;
        }
    }

    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (scanf("%lf ", &((pols->f)[i][j])) == EOF)
            {
                printf("\e[32mERRO:\e[39m Input mal formatado. Esperando valor na matriz");
                return NULL;
            }
        }
    }
    return pols;
}

/*!
    \brief Calcula termos(valores da matriz) para calcular ajuster de curva pelo método dos Minimos Quadrados
    \param x Valores de x tabelados
    \param n Quantidade de x tabelados 
    \param grau Grau desejado do polinomio
    \return Vetor de termos, onde termos[i+j] corresponde a Σ(Gi(Xk)*Gj(Xk))
*/
double *calculaTermosMinimosQuadrados(double *x, int n, int grau)
{
    // Como termo[i][j] = termo[0][i+j] (diagonais secundárias iguais), tudo é calculado em apenas uma unica linha.
    int nGrau = grau + 1;
    double *termos = calloc(2 * nGrau, sizeof(double));
    // termos[0] = 0;
    for (int i = 0; i < nGrau; i++)
    {
        termos[i] = 0;
    }

    double currentPow = 1;
    // Para cada x[i]
    for (int ix = 0; ix < n; ix++, currentPow = 1)
    {
        double ixValue = x[ix];
        // Acumula valor da potencia para cada respectivo termo (percorre varias vezes a mesma linha para evitar recalculo da potencia)
        for (int it = 0; it < 2 * nGrau; it++, currentPow *= ixValue)
        {
            termos[it] += currentPow;
        }
    }
    return termos;
}
/*!
    \brief A partir dos termos calculados, gera, inicializa e triangula matriz LU para ser utilizada posteriormente nos calculos
    \param termos Termos onde  termos[i+j] = Σ(Gi(Xk)*Gj(Xk) = lu->A[i][j]
    \param lu Instancia não inicalizada(apenas alocada) de FatoracaoLU
    \param grau Grau desejado do polinomio
    \param pivota Se verdadeiro, utiliza pivoteamento
    \return tempo de execução da triangulação
*/
int montaLUMinimosQuadrados(double *termos, FatoracaoLU *lu, int grau, bool pivota)
{
    int nGrau = grau + 1;
    // Preenche matriz A
    for (int i = 0; i < nGrau; i++)
    {
        for (int j = 0; j < nGrau; j++)
        {
            double v = termos[i + j];
            lu->A[i][j] = v;
            lu->L[i][j] = v;
        }
    }
    return triangulaLU(lu, pivota);
}
/*!
    \brief Calcula coeficiente do polinomio do método de Minimos Quadrados
    \param x Valores de x tabelados
    \param n Quantidade de x tabelados
    \param lu Instancia calculada e triangulada dos termos do método de Minimos Quadrados
    \param y Vetor de Yi
    \param grau Grau desejado do polinomio
    \param pivota Se verdadeiro, utiliza pivoteamento
    \return tempo de execução da resolução dos SL
*/
int calculaPolinomioMinimosQuadrados(double *x, int n, FatoracaoLU *lu, double *y, double *coef, int grau, bool pivota)
{
    int time = 0;
    double somY = 0;
    int nGrau = grau + 1;
    // Para cada grau do polinomio
    for (int k = 0; k < nGrau; ++k, somY = 0)
    {
        // Para cada valor tabelado de f(x)
        for (int i = 0; i < n; i++)
        {
            somY += y[i] * pow(x[i], k);
        }
        lu->b[k] = somY;
    }

    time += calculaY(lu);
    time += calculaX(lu, coef);

    if (pivota)
    {

        double *coefCopy = calloc(n, sizeof(double));
        unsigned int *t = lu->trocas;
        for (int i = 0; i < nGrau; i++)
            coefCopy[t[i]] = coef[i];
        // Repassa para vetor X original
        for (int i = 0; i < nGrau; i++)
            coef[i] = coefCopy[i];
        free(coefCopy);
        // Revere troca de linhas em A e LU
        // reverteTrocaLinhaLogica(lu);
    }
    return time;
}

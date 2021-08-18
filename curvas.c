#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h> /* getopt */
#include "utils.h"
#include "polinomio.h"
#include "calculaInversa.h"

#include <likwid.h>

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
    fprintf(stderr, "Forma de uso: %s [ -n <ordem> ] \n", progname);
    exit(1);
}

/**
 * Programa principal
 * Forma de uso: matrixInv -p
 * -p: parâmetro opcional indicando que deve ser feito pivoteamento parcial durante o processo de triangularização. Na ausência deste parâmetro, não deve haver pivoteamento;
 */
inputPolinomial *inputs;

int main(int argc, char *argv[])
{

    // metricas metrica, metmrica;
    bool pivo = false;
    bool run_likwid = false;
    int n, m, grau;
    /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

    char *opts = "pl";
    int c = getopt(argc, argv, opts);

    while (c != -1)
    {
        switch (c)
        {
        case 'p':
            pivo = true;
            break;
        case 'l':
            run_likwid = true;
            break;
        default:
            usage(argv[0]);
        }
        c = getopt(argc, argv, opts);
    }
    /* ============================================================== */
    if (run_likwid)
        LIKWID_MARKER_INIT;

    for (inputs = lerFuncoes(); inputs != NULL; inputs = lerFuncoes())
    {

        n = inputs->n;
        m = inputs->m;
        grau = n - 1;
        // grau = 2;
        double *coeficientes;

        FatoracaoLU *luMQ = alocaFatoracaoLU(grau + 1);
        double *termos = calculaTermosMinimosQuadrados(inputs->x, n, grau);
        montaLUMinimosQuadrados(termos, luMQ, grau, pivo);
        for (int i = 0; i < m; i++)
        {

            coeficientes = calloc(n, sizeof(double));
            LIKWID_MARKER_START("InterpoladorSL");
            calculaInterPolSL(inputs->x, inputs->f[i], n, coeficientes, pivo);
            if (!run_likwid) printVector(coeficientes, n);
            LIKWID_MARKER_STOP("InterpoladorSL");

            if (run_likwid)
            {
                LIKWID_MARKER_START("InterpoladorNewton");
                interPolNewton *interpolador = alocaInterPolNewton(n, inputs->x, inputs->f[i]);
                completa_interPolNewton(interpolador, coeficientes);
                LIKWID_MARKER_STOP("InterpoladorNewton");
            }

            LIKWID_MARKER_START("MinimosQuadrados");
            calculaPolinomioMinimosQuadrados(inputs->x, n, luMQ, inputs->f[i], coeficientes, grau, pivo);
            if (!run_likwid) printVector(coeficientes, n);
            LIKWID_MARKER_STOP("MinimosQuadrados");
        }
        liberaFatoracaoLU(luMQ);
    }
    if (run_likwid)
        LIKWID_MARKER_CLOSE;
}

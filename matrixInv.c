#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h> /* getopt */
#include "calculaInversa.h"
#include "calculaInversaOtm.h"
#include "utils.h"

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
int main(int argc, char *argv[])
{
    LIKWID_MARKER_INIT;
    FatoracaoLU *sisLU;
    FatoracaoLUOtm *sisOtm;
    metricas metrica, metricaOtm;
    double **Transp_INV;
    bool pivo = false;

    /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

    char *opts = "p";
    int c = getopt(argc, argv, opts);

    while (c != -1)
    {
        switch (c)
        {
        case 'p':
            pivo = true;
            break;
        default:
            usage(argv[0]);
        }
        c = getopt(argc, argv, opts);
    }
    /* ============================================================== */

    for (sisLU = lerMatriz(); sisLU != NULL; sisLU = lerMatriz())
    {
        sisOtm = cp2otm(sisLU);
        Transp_INV = alocaMatrizQ(sisLU->n);
        LIKWID_MARKER_START("calculaInversa");
        calculaInversa(sisLU, Transp_INV, &metrica, pivo);
        LIKWID_MARKER_STOP("calculaInversa");

        LIKWID_MARKER_START("calculaInversaOtm");
        // calculaInversaOtm(sisOtm, Transp_INV, &metricaOtm, pivo);
        LIKWID_MARKER_STOP("calculaInversaOtm");

        printResultado(sisLU, Transp_INV, &metrica);

        liberaMatrizQ(Transp_INV, sisLU->n);

        liberaFatoracaoLU(sisLU);
        liberaFatoracaoLUOtm(sisOtm);
    }
    LIKWID_MARKER_CLOSE;
}
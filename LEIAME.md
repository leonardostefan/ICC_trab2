# CI1164 Trabalho 2 (Teste e Relatório não finalizados)
**Aluno:** Leonardo Stefan
**dInf:** ls16
**GRR**: 20163052


Documentação referente ao trabalho 2 da disciplina de Introdução a Computação Ciêntifica do ERE2021.

**Relátorio Pendente a Finalizar**
Os testes de execução e plot dos graficos ainda não foram executados, sendo assim o relatorio também não.

## Execução 
Para compilar o projeto  basta executar `$ make` no terminal.

Para executar o programa basta executar `$ ./curvas < data ` onde data é o caminho do arquivo de dados com as entradas conforme o padrão da [especificação](./ESPECIFICACAO.MD)




## Arquivos
- **curvas.c**: Corpo principal do projeto, loop de leitura e execução do algoritmo;
- **utils.h**: Biblioteca auxiliar fornecida pelo professor sem modificação;
- **calculaInversa.h**: Biblioteca com as funções especificadas para a execução do projeto do trabalho 1;
- **calculaInversaOtm.h**: Biblioteca com as funções  do trabalho 1 modificadas (tentativa de otimização);
- **polinomial.h**: Biblioteca com as funções de Interpolação Polinomial e de ajuste de Curvas Polinomias
- [ESPECIFICACAO.MD](./ESPECIFICACAO.MD): especificação original do projeto;
- **Makefile**: compilação do projeto com `make`;
- **testes/\*** e **sample/**: Diretório  com alguns inputs de tese utilizado

## Relatorio Implementação/Execução

**Relátorio Pendente a Finalizar**

### Modificações e desempenho Obtido
**Relátorio Pendente a Finalizar**

Algumas otimizações ja estavam feitas no trabalho 1, como a utilização da transposta da inversa, foi tentado utilizar o alocamento em linha, pré calculando o endereço simulando o acesso de ponteiros de ponteiros porém não houve melhora significativa no desempenho 
nos testes iniciais (testes completos pendentes), o mesmo aconteceu para loopunroll.

### Polinomios de ajuste de curva e interpolação
Os algoritmos implementados de interpolação e ajuste de curva funcionaram como o esperado.
Sempre que possivel foi reaproveitado os valores já calculados, como é no caso do reaproveitamento da ultima potencia X^n calculada para calcular X^(n+1) e nas diagonais do Sistema Linear do Método dos Mínimos Quadrados.

O ajuste de Curvas ainda foi implementado de forma a poder escolher um valor arbitrario para o grau do polinomio.

## Resultado dos testes
 Pendente
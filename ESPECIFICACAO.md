<div role="main" id="yui_3_17_2_1_1629051927545_83"><span id="maincontent"></span><h2>Trabalho 02</h2><div id="intro" class="box py-3 generalbox boxaligncenter"><div class="no-overflow" id="yui_3_17_2_1_1629051927545_106"><div id="intro" class="box generalbox boxaligncenter">
<div class="no-overflow" id="yui_3_17_2_1_1539792241630_255">
<p class="no-overflow"><span style="font-size: x-large;"><strong>Trabalho 02</strong></span></p>
<p id="yui_3_17_2_1_1629051927545_115"><span style="font-size: large;">O objetivo deste trabalho é melhorar o desempenho e comparar a performance da resolução de Sistemas Lineares por Fatoração LU desenvolvida no </span><span class="autolink" style="font-size: large;"><a class="autolink" title="Trabalho 01" href="https://moodle.c3sl.ufpr.br/mod/assign/view.php?id=28417">Trabalho 01</a></span><span style="font-size: large;">, aplicada a um problema de Interpolação e Ajuste de Curvas.<br></span></p>
<p><span style="font-size: large;">Você deve aplicar técnicas de melhoria de desempenho estudadas em aula <strong>às funções</strong>:</span></p>
<ol id="yui_3_17_2_1_1629051927545_113">
<li><span style="font-size: large;">Triangularização (geração da matriz&nbsp;<strong>U</strong>&nbsp;do <a class="autolink" title="Trabalho 01" href="https://moodle.c3sl.ufpr.br/mod/assign/view.php?id=28417">Trabalho 01</a>)<br></span></li>
<li id="yui_3_17_2_1_1629051927545_112"><span style="font-size: large;">Cálculo da matriz de coeficientes do SL usado no&nbsp;<strong>Ajuste de Curvas</strong><br></span></li>
</ol>
<p><span style="font-size: large;">Para cada função, você deve ESCREVER um texto explicando as otimizações implementadas justificando por que estas modificações melhoram seu desempenho.</span></p>
<p id="yui_3_17_2_1_1629051927545_105"><span style="font-size: large;" id="yui_3_17_2_1_1629051927545_104">Você também deve resolver um problema de <strong id="yui_3_17_2_1_1629051927545_114">Interpolação Polinomial</strong> e <strong>Ajuste de Curvas Polinomial</strong>. Neste problema, seu programa deve ler da entrada padrão tabelas de pontos e gerar os coeficientes dos polinômios de grau&nbsp;<strong>n-1</strong> em cada método.</span></p>
<p><span style="font-size: large;">Os sistemas lineares usados na Interpolação e Ajuste de Curvas devem ser resolvidos usando apenas Fatoração LU.</span></p>
<p><span style="font-size: large;">Os dados de entrada devem ser lidos da entrada padrão e&nbsp;seguir o seguinte formato:</span></p>
<p dir="ltr" style="margin-left: 90px;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; n m<br>&nbsp; x<sub>1</sub>&nbsp; <span class="Apple-tab-span"> </span>x<sub>2</sub>&nbsp; <span class="Apple-tab-span"> </span>... &nbsp; x<sub>n</sub></span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; f<sub>1</sub>(x<sub>1</sub>)&nbsp; f<sub>1</sub>(x<sub>2</sub>)&nbsp; ... &nbsp; f<sub>1</sub>(<span style="font-family: 'courier new', courier, monospace; font-size: large;">x<sub>n</sub>)</span><sub><span style="font-family: 'courier new', courier, monospace; font-size: large;"></span></sub></span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; f<sub>2</sub>(x<sub>1</sub>)&nbsp; f<sub>2</sub>(x<sub>2</sub>)&nbsp; ... &nbsp; f<sub>2</sub>(x<sub>n</sub>)</span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; ... &nbsp; &nbsp;<span class="Apple-tab-span"> </span>... &nbsp;&nbsp;<span class="Apple-tab-span"> </span>... &nbsp; ...</span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; f<sub>m</sub>(x<sub>1</sub>)&nbsp; f<sub>m</sub>(x<sub>2</sub>)&nbsp; ... &nbsp; f<sub>m</sub>(x<sub>n</sub>)</span><span style="font-family: arial, helvetica, sans-serif; font-size: large;">&nbsp;</span></p>
<p dir="ltr" style="margin-left: 90px;"><span style="font-family: arial, helvetica, sans-serif; font-size: large;">Onde,</span></p>
<p style="margin-left: 90px;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; n &nbsp; <span class="Apple-tab-span"> </span>número de valores tabelados<br>&nbsp; m &nbsp; <span class="Apple-tab-span"> </span>número de funções tabeladas</span><span style="font-family: 'courier new', courier, monospace; font-size: large;"><strong></strong></span>&nbsp; &nbsp; &nbsp; &nbsp; <br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; x<sub>i</sub>&nbsp; <span class="Apple-tab-span"> </span>valores tabelados, i = 1..n</span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp; f<sub>j</sub>(x<sub>i</sub>)&nbsp; funções nos valores tabelados, j = 1..m, i = 1..n</span></p>
<p><span style="font-size: large;">&nbsp;</span></p>
<p><span style="font-size: large;">Os dados de saída devem seguir o&nbsp; seguinte formato:</span></p>
<p style="margin-left: 90px;"><span style="font-size: large;"></span><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;a<sub>11</sub>&nbsp; a<sub>12</sub>&nbsp; ...&nbsp; a<sub>1n <br></sub>&nbsp;b<sub>11</sub>&nbsp; b<sub>12</sub>&nbsp; ...&nbsp; b<sub>1n</sub><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;a<sub>21</sub>&nbsp; a<sub>22</sub>&nbsp; ...&nbsp; a<sub>2n</sub>&nbsp;<br><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;b<sub>21</sub>&nbsp; b<sub>22</sub>&nbsp; ...&nbsp; b<sub>2n</sub></span></span><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;<span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">...</span></span></span> <span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">...</span></span></span>&nbsp; ...&nbsp;&nbsp;<sub><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">...</span></span></span> </sub><br><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;a<sub>m1</sub>&nbsp; a<sub>m2</sub>&nbsp; ...&nbsp; a<sub>mn </sub><br><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;b<sub>m1</sub>&nbsp; b<sub>m2</sub>&nbsp; ...&nbsp; b<sub>mn</sub></span></span></span></span></span></span><br></span></span></p>
<p dir="ltr"><span>&nbsp;&nbsp;<span style="font-size: large;">Onde,</span></span></p>
<p dir="ltr" style="margin-left: 90px;"><span style="font-size: large;"><span style="font-family: 'courier new', courier, monospace;"><span>&nbsp; n &nbsp;&nbsp;</span><span class="Apple-tab-span"></span><span>número de valores tabelados<br><span>&nbsp; m &nbsp;&nbsp;</span><span class="Apple-tab-span"></span><span>número de funções</span></span></span><span style="font-family: 'courier new', courier, monospace;"><br></span><span style="font-family: 'courier new', courier, monospace;">&nbsp; a<sub>ji</sub>&nbsp; coeficientes&nbsp;<span class="Apple-tab-span"></span></span><span style="font-family: 'courier new', courier, monospace;">do polinômio gerado pela <strong>Interpolação</strong><span>, j = 1..m</span><span>, i = 1..n&nbsp;<span><br></span><span>&nbsp; b<sub><span>ji</span></sub>&nbsp; coeficientes&nbsp;<span class="Apple-tab-span"></span></span><span>do&nbsp;<span>polinômio gerado pel</span>o <strong>Ajuste de Curvas</strong>, j = 1..m, i = 1..n</span></span></span></span></p>
<p style="margin-left: 90px;"><span style="font-family: 'courier new', courier, monospace; font-size: large;">&nbsp;</span></p>
<p><span style="font-size: large;">Os dados de entrada podem ser gerados pelo comando abaixo, acessível pelo git:</span></p>
<p><span style="font-size: large; font-family: 'courier new', courier, monospace;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; gera_entrada&nbsp; n</span></p>
<p></p>
<p><strong><span style="font-size: x-large;">Análise de Desempenho</span></strong></p>
<p><span style="font-size: large;">As análises devem ser descritas sob a forma de um <strong>trabalho acadêmico</strong>, e entregues em formato PDF. O trabalho deve conter:</span></p>
<ul>
<li><span style="color: #000000; font-size: large;">Introdução, descrevendo sucintamente o que está sendo apresentado</span></li>
<li><span style="font-size: large;">Descrição detalhada do computador utilizado para os experimentos</span></li>
<li><span style="font-size: large;">Descrição de como rodar os experimentos</span></li>
<li><span style="font-size: large;">Descrição das otimizações efetuadas em cada uma das funções</span></li>
<li><span style="font-size: large;">Gráficos reportando os testes para cada função otimizada, com legenda descrevendo as figuras.</span><span style="font-size: large;"></span></li>
</ul>
<p><strong><span style="font-size: large;">É imprescindível que sejam respeitadas as seguintes condições:</span></strong></p>
<ol>
<li>
<p><span style="font-size: large;">Os códigos devem ser compilados com GCC e as opções: <b>-O3 -mavx -march=native</b>;</span></p>
</li>
<li>
<p><span style="font-size: large;">Os testes devem utilizar os mesmos parâmetros e em igualdade de condições;</span></p>
</li>
<li>
<p><span style="font-size: large;">O código deve ser instrumentados com a biblioteca do <b>LIKWID</b> para que se possa separar os contadores de cada função.</span></p>
</li>
<li>
<p><span style="font-size: large;">Você deve apresentar a arquitetura do processador utilizado nos testes no seu texto. Estas informações podem ser obtidas com o comando "LIKWID-topology -g -c".</span></p>
</li>
<li>
<p><span style="font-size: large;">Os códigos devem ser compilados na mesma máquina utilizada para os testes;</span></p>
<ul>
<li><span style="color: #000000; font-size: large;">Utilize os computadores HP EliteDesk do Lab3 (máquinas i29 a i40)</span></li>
<li><span style="font-size: large;"><span style="color: #000000;">Antes de rodar experimentos, é necessário </span><strong><span style="color: #ff0000;">FIXAR a frequência do processador.</span></strong></span></li>
<li><span style="font-size: large;">Utilizaremos SEMPRE o mesmo core (ex. 03). Execute a seguinte linha de comando:</span></li>
</ul>
</li>
</ol>
<p style="margin-left: 60px;"><span style="font-size: large;"><strong><span style="font-family: courier new, courier, monospace;">echo "performance" &gt; /sys/devices/system/cpu/cpufreq/policy3/scaling_governor</span></strong></span></p>
<ul>
<li style="list-style-type: none;">
<ul>
<li>
<p><span style="font-size: large;">Lembre-se de utilizar o CORE 03 na hora de rodar os experimentos:</span></p>
</li>
</ul>
</li>
</ul>
<p style="margin-left: 60px;"><span style="font-size: large;"><strong><span style="font-family: courier new, courier, monospace;">likwid-perfctr -C 3 ...</span></strong></span></p>
<ul>
<li style="list-style-type: none;">
<ul>
<li>
<p><span style="font-size: large;">Após os experimentos, retorne frequência original</span></p>
</li>
</ul>
</li>
</ul>
<p style="margin-left: 60px;"><span style="font-family: 'courier new', courier, monospace; font-size: large;"><strong>echo "powersave" &gt; /sys/devices/system/cpu/cpufreq/policy3/scaling_governor&nbsp; </strong></span></p>
<p style="margin-left: 30px;"><span style="font-size: large;">Para analisar o desempenho das funções, você deve efetuar uma série de testes.</span></p>
<ul>
<li>
<p><span style="font-size: large;"><b>Cada teste</b> deve ser reportado sob a forma de um gráfico de linhas com eixos&nbsp; TAMANHO (abcissa) × INDICADOR DO TESTE (ordenada).<br>No eixo das abcissas os gráficos representam a quantidade de pontos da tabela<br></span></p>
</li>
<ul>
<li>
<p><span style="font-size: large;">Cada teste deve ser executado para os seguintes valores de&nbsp;&nbsp;<strong>n</strong><strong></strong>:&nbsp; {10, 32, 50, 64, 100, 128, 200, 256, 300, 400, 512, 1000}</span></p>
</li>
<li>
<p><span style="font-size: large;">As entradas do programa para cada <strong>n</strong><strong> </strong>devem ser geradas pelo comando: <span style="font-family: courier new, courier, monospace;">gera_entrada n</span></span><span style="font-size: large; font-family: courier new, courier, monospace;"></span></p>
</li>
</ul>
</ul>
<p><span style="font-size: large;">Os seguintes testes devem ser executados para <strong>cada função</strong>,<strong>&nbsp;</strong>um gráfico para cada teste de cada função. No caso da função de Triangularização, colocar no mesmo gráfico o resultado dos testes da função sem otimização (<a class="autolink" title="Trabalho 01" href="https://moodle.c3sl.ufpr.br/mod/assign/view.php?id=28417">Trabalho 01</a>) e com otimização (Trabalho 02);</span></p>
<ol>
<li>
<p><span style="font-size: large;"><b>Teste de tempo:</b> mostra o tempo médio do cálculo da <strong>função, em milisegundos</strong> (utilize a função "<a href="https://web.inf.ufpr.br/danielw/cursos/ci164-20162/ci164-2015-02-trabalho1#FuncaoTempo" class="internal-link"><span class="internal-link">timestamp()</span></a>" ou o próprio LIKWID para medir o tempo).&nbsp;</span><span style="font-size: large;">O tempo deve ser mostrado em&nbsp;escala <strong style="font-size: large;">logarítmica</strong>&nbsp;no gráfico.</span></p>
</li>
<li>
<p><span style="font-size: large;"><b>Banda de Memória:</b> utilizar o grupo L3 do LIKWID, e apresentar o resultado de "<strong>Memory bandwidth [MBytes/s]</strong>";</span></p>
</li>
<li>
<p><span style="font-size: large;"><b>Cache miss L2:</b> utilizar o grupo L2CACHE do LIKWID, e apresentar o resultado de "<strong>data cache miss ratio</strong>";</span></p>
</li>
<li>
<p><span style="font-size: large;"><b>Operações aritméticas:</b> utilizar o grupo FLOPS_DP do LIKWID e reportar FLOPS_DP e FLOPS_AVX como duas linhas separadas no&nbsp;<strong>mesmo gráfico</strong>, em "<strong>MFLOP/s</strong>"</span></p>
</li>
</ol>
<p></p>
<h3><span style="font-size: 1.75rem;">Acesso aos arquivos</span></h3>
<p><span style="font-size: large;">Os arquivos para este exercício encontram-se no git em</span></p>
<p><span style="font-size: large;"><a href="https://gitlab.c3sl.ufpr.br/nicolui/ci1164_2020-trab02.git" target="_blank" style="background-color: #ffffff; font-size: 1rem;">https://gitlab.c3sl.ufpr.br/nicolui/ci1164_2020-trab02.git</a></span></p>
<p><span style="font-size: large;">ou via linha de comando:</span></p>
<p><span style="font-size: large;">git clone git@gitlab.c3sl.ufpr.br:nicolui/ci1164_2020-trab02.git</span></p>
<h3></h3>
<div id="parent-fieldname-text-77a8d7355be84cf59846ce79a15461bc">
<p><span style="font-size: x-large;"><strong>Produto a ser Entregue</strong></span></p>
</div>
<p class="no-overflow"><span style="font-size: large;">O trabalho deve ser desenvolvido por um grupo composto por <strong>no máximo DOIS</strong> alunos regularmente matriculados na disciplina. O grupo DEVE SER O MESMO do <a class="autolink" title="Trabalho 01" href="https://moodle.c3sl.ufpr.br/mod/assign/view.php?id=28417">Trabalho 01</a>.</span></p>
<div>
<p><span style="font-size: large;">Cada grupo deve entregar via MOODLE um pacote de software completo contendo os fontes em <b>linguagem C</b>. O pacote deve ser arquivado e compactado com&nbsp;<strong>zip</strong> em um arquivo chamado login1.zip (se grupo com 1 membro) ou login1-login2.zip (se grupo com 2 membros), onde login1 e login2 são os logins dos alunos que compõem o grupo.</span></p>
</div>
<div><span style="font-size: large;">O arquivo contendo o relatório deve ser nomeado <strong>RELATORIO-login1(-login2).pdf</strong> <span style="text-decoration: line-through;"><br></span></span></div>
<div><span style="font-size: large;"></span></div>
<div>
<p><span style="font-size: x-large;"><strong>Critérios de Avaliação</strong></span></p>
<p><span style="font-size: large;">A</span><span style="font-size: large;">PENAS OS TRABALHOS QUE FUNCIONAREM SERÃO CORRIGIDOS. Se o trabalho não compilar ou acusar falha de segmentação (Segmentation fault) prematura durante os testes realizados pelo professor (sem que qualquer operação se efetue a contento) ou não produzir a solução correta, trará para o grupo NOTA 0 (ZERO). Também receberão NOTA 0 (ZERO) trabalhos plagiados de qualquer fonte, e/ou com códigos idênticos ou similares. Além disso, apenas trabalhos entregues no prazo marcado receberão nota.</span></p>
<p><span style="font-size: large;">Os itens de avaliação do trabalho e respectivas pontuações são:</span></p>
<ul>
<li><span style="font-size: large;">Qualidade da documentação: arquivo RELATORIO-login1.pdf (20 pontos)</span>
<ul>
<li><span style="font-size: large;">Organização do texto</span></li>
<li><span style="font-size: large;">Gráficos e legendas apropriados</span></li>
</ul>
</li>
<li><span style="font-size: large;">Otimizações efetuadas (80)</span>
<ul>
<li><span style="font-size: large;">Qualidade/Corretude</span></li>
<li><span style="font-size: large;">Dificuldade/complexidade das otimizações</span></li>
<li><span style="font-size: large;">Desempenho obtido</span></li>
<li><span style="font-size: large;">Justificativas/Análises</span></li>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "help.h"

#define LINES_PER_PAGE 20

void print_help_header() {
    printf(INFO_COLOR "=== RUDIS 0.0.1 - SISTEMA DE AJUDA ===\n" RESET);
}

void print_general_help() {
    print_help_header();
    printf("\n" BOLD "COMANDOS DO SISTEMA:\n" RESET);
    printf("  help                    - Mostra esta ajuda geral\n");
    printf("  help <função>           - Ajuda específica de uma função\n");
    printf("  help <página>           - Navega pelas páginas de ajuda\n");
    printf("  exit, quit              - Sai do programa\n");
    printf("  set lang pt|en          - Muda o idioma\n");
    printf("  clear                   - Limpa a tela\n");
    printf("  vars                    - Lista variáveis definidas\n");
    
    printf("\n" BOLD "CATEGORIAS DE FUNÇÕES:\n" RESET);
    printf("  * Matemáticas Básicas   - +, -, *, /, %%, ^, !\n");
    printf("  * Funções Matemáticas   - sqrt, sin, cos, log, exp, abs\n");
    printf("  * Funções Estatísticas  - mean, median, std, variance, mode\n");
    printf("  * Funções Financeiras   - pv, fv, pmt, npv, irr, si, ci\n");
    printf("  * Aliases Português     - raiz, sen, media, mediana, vpl, tir\n");
    
    printf("\n" BOLD "EXEMPLOS RÁPIDOS:\n" RESET);
    printf("  > 5 + 3 * 2\n");
    printf("  > x = 10\n");
    printf("  > sqrt(x) + 2^3\n");
    printf("  > mean(1, 2, 3, 4, 5)\n");
    printf("  > pv(0.05, 10, 100)\n");
    printf("  > media(10, 20, 30)\n");
    
    printf("\nDigite " BOLD "help 1" RESET " para lista completa de funções.\n");
}

void print_function_help(const char* function_name) {
    print_help_header();
    printf("\n");
    
    // MATEMÁTICAS BÁSICAS
    if (strcmp(function_name, "+") == 0) {
        printf(BOLD "Operador: + (Adição)\n" RESET);
        printf("Sintaxe: a + b\n");
        printf("Descrição: Soma dois valores numéricos.\n");
        printf("Exemplo: 5 + 3 retorna 8\n");
    }
    else if (strcmp(function_name, "-") == 0) {
        printf(BOLD "Operador: - (Subtração)\n" RESET);
        printf("Sintaxe: a - b\n");
        printf("Descrição: Subtrai o segundo valor do primeiro.\n");
        printf("Exemplo: 10 - 4 retorna 6\n");
    }
    else if (strcmp(function_name, "*") == 0) {
        printf(BOLD "Operador: * (Multiplicação)\n" RESET);
        printf("Sintaxe: a * b\n");
        printf("Descrição: Multiplica dois valores.\n");
        printf("Exemplo: 6 * 7 retorna 42\n");
    }
    else if (strcmp(function_name, "/") == 0) {
        printf(BOLD "Operador: / (Divisão)\n" RESET);
        printf("Sintaxe: a / b\n");
        printf("Descrição: Divide o primeiro valor pelo segundo.\n");
        printf("Exemplo: 15 / 3 retorna 5\n");
        printf("Nota: Retorna erro se b = 0\n");
    }
    else if (strcmp(function_name, "%") == 0) {
        printf(BOLD "Operador: %% (Módulo)\n" RESET);
        printf("Sintaxe: a %% b\n");
        printf("Descrição: Retorna o resto da divisão inteira.\n");
        printf("Exemplo: 10 %% 3 retorna 1\n");
    }
    else if (strcmp(function_name, "^") == 0) {
        printf(BOLD "Operador: ^ (Potência)\n" RESET);
        printf("Sintaxe: a ^ b\n");
        printf("Descrição: Eleva a à potência de b.\n");
        printf("Exemplo: 2 ^ 8 retorna 256\n");
    }
    else if (strcmp(function_name, "!") == 0) {
        printf(BOLD "Operador: ! (Fatorial)\n" RESET);
        printf("Sintaxe: a!\n");
        printf("Descrição: Calcula o fatorial de um número inteiro.\n");
        printf("Exemplo: 5! retorna 120\n");
        printf("Nota: Funciona apenas com inteiros não-negativos\n");
    }
    
    // FUNÇÕES MATEMÁTICAS
    else if (strcmp(function_name, "sqrt") == 0 || strcmp(function_name, "raiz") == 0) {
        printf(BOLD "Função: sqrt / raiz (Raiz Quadrada)\n" RESET);
        printf("Sintaxe: sqrt(x) ou raiz(x)\n");
        printf("Parâmetros: x - número não negativo\n");
        printf("Retorna: Raiz quadrada de x\n");
        printf("Exemplo: sqrt(25) retorna 5\n");
        printf("Exemplo: raiz(16) retorna 4\n");
        printf("Aplicação: Cálculo de distâncias, áreas, desvio padrão\n");
    }
    else if (strcmp(function_name, "sin") == 0 || strcmp(function_name, "sen") == 0) {
        printf(BOLD "Função: sin / sen (Seno)\n" RESET);
        printf("Sintaxe: sin(x) ou sen(x)\n");
        printf("Parâmetros: x - ângulo em radianos\n");
        printf("Retorna: Seno do ângulo x\n");
        printf("Exemplo: sin(0) retorna 0\n");
        printf("Exemplo: sen(1.5708) retorna ~1 (π/2)\n");
        printf("Aplicação: Ondas, oscilações, processamento de sinais\n");
    }
    else if (strcmp(function_name, "cos") == 0) {
        printf(BOLD "Função: cos (Cosseno)\n" RESET);
        printf("Sintaxe: cos(x)\n");
        printf("Parâmetros: x - ângulo em radianos\n");
        printf("Retorna: Cosseno do ângulo x\n");
        printf("Exemplo: cos(0) retorna 1\n");
        printf("Exemplo: cos(3.1416) retorna ~-1 (π)\n");
        printf("Aplicação: Movimento harmônico, rotações\n");
    }
    else if (strcmp(function_name, "tan") == 0) {
        printf(BOLD "Função: tan (Tangente)\n" RESET);
        printf("Sintaxe: tan(x)\n");
        printf("Parâmetros: x - ângulo em radianos\n");
        printf("Retorna: Tangente do ângulo x\n");
        printf("Exemplo: tan(0) retorna 0\n");
        printf("Exemplo: tan(0.7854) retorna ~1 (π/4)\n");
        printf("Aplicação: Triângulos, inclinações, sombras\n");
    }
    else if (strcmp(function_name, "log") == 0 || strcmp(function_name, "log10") == 0) {
        printf(BOLD "Função: log / log10 (Logaritmo Base 10)\n" RESET);
        printf("Sintaxe: log(x) ou log10(x)\n");
        printf("Parâmetros: x - número positivo\n");
        printf("Retorna: Logaritmo base 10 de x\n");
        printf("Exemplo: log(100) retorna 2\n");
        printf("Exemplo: log10(1000) retorna 3\n");
        printf("Aplicação: Escalas logarítmicas, pH, decibéis\n");
    }
    else if (strcmp(function_name, "ln") == 0) {
        printf(BOLD "Função: ln (Logaritmo Natural)\n" RESET);
        printf("Sintaxe: ln(x)\n");
        printf("Parâmetros: x - número positivo\n");
        printf("Retorna: Logaritmo natural de x (base e)\n");
        printf("Exemplo: ln(2.71828) retorna ~1\n");
        printf("Aplicação: Crescimento contínuo, juros compostos\n");
    }
    else if (strcmp(function_name, "exp") == 0) {
        printf(BOLD "Função: exp (Exponencial)\n" RESET);
        printf("Sintaxe: exp(x)\n");
        printf("Parâmetros: x - expoente\n");
        printf("Retorna: e elevado a x\n");
        printf("Exemplo: exp(1) retorna ~2.71828\n");
        printf("Exemplo: exp(0) retorna 1\n");
        printf("Aplicação: Crescimento exponencial, decaimento\n");
    }
    else if (strcmp(function_name, "abs") == 0) {
        printf(BOLD "Função: abs (Valor Absoluto)\n" RESET);
        printf("Sintaxe: abs(x)\n");
        printf("Parâmetros: x - qualquer número\n");
        printf("Retorna: Valor absoluto de x\n");
        printf("Exemplo: abs(-5.5) retorna 5.5\n");
        printf("Exemplo: abs(10) retorna 10\n");
        printf("Aplicação: Distâncias, erros absolutos, magnitude\n");
    }
    
    // FUNÇÕES ESTATÍSTICAS
    else if (strcmp(function_name, "mean") == 0 || strcmp(function_name, "media") == 0) {
        printf(BOLD "Função: mean / media (Média Aritmética)\n" RESET);
        printf("Sintaxe: mean(val1, val2, ...) ou media(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para calcular a média\n");
        printf("Retorna: Média dos valores fornecidos\n");
        printf("Exemplo: mean(1, 2, 3, 4, 5) retorna 3\n");
        printf("Exemplo: media(10, 20, 30) retorna 20\n");
        printf("Aplicação: Notas médias, gastos médios, desempenho\n");
    }
    else if (strcmp(function_name, "median") == 0 || strcmp(function_name, "mediana") == 0) {
        printf(BOLD "Função: median / mediana (Mediana)\n" RESET);
        printf("Sintaxe: median(val1, val2, ...) ou mediana(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para calcular a mediana\n");
        printf("Retorna: Valor do meio dos dados ordenados\n");
        printf("Exemplo: median(1, 3, 5) retorna 3\n");
        printf("Exemplo: mediana(1, 2, 3, 4) retorna 2.5\n");
        printf("Aplicação: Análise de renda, preços, dados com outliers\n");
    }
    else if (strcmp(function_name, "std") == 0 || strcmp(function_name, "desvio") == 0) {
        printf(BOLD "Função: std / desvio (Desvio Padrão)\n" RESET);
        printf("Sintaxe: std(val1, val2, ...) ou desvio(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para calcular o desvio\n");
        printf("Retorna: Desvio padrão amostral dos valores\n");
        printf("Exemplo: std(10, 20) retorna ~7.07\n");
        printf("Exemplo: desvio(5, 5, 5) retorna 0\n");
        printf("Aplicação: Volatilidade, controle de qualidade, risco\n");
    }
    else if (strcmp(function_name, "variance") == 0 || strcmp(function_name, "variancia") == 0) {
        printf(BOLD "Função: variance / variancia (Variância)\n" RESET);
        printf("Sintaxe: variance(val1, val2, ...) ou variancia(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para calcular a variância\n");
        printf("Retorna: Variância amostral dos valores\n");
        printf("Exemplo: variance(1, 2, 3) retorna 1\n");
        printf("Exemplo: variancia(5, 10, 15) retorna 25\n");
        printf("Aplicação: Análise de risco, dispersão de dados\n");
    }
    else if (strcmp(function_name, "mode") == 0 || strcmp(function_name, "moda") == 0) {
        printf(BOLD "Função: mode / moda (Moda)\n" RESET);
        printf("Sintaxe: mode(val1, val2, ...) ou moda(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para encontrar a moda\n");
        printf("Retorna: Valor mais frequente no conjunto\n");
        printf("Exemplo: mode(1, 1, 2, 2, 2, 3) retorna 2\n");
        printf("Exemplo: moda(5, 5, 10, 10, 10) retorna 10\n");
        printf("Aplicação: Pesquisas de preferência, produtos mais vendidos\n");
    }
    else if (strcmp(function_name, "sum") == 0 || strcmp(function_name, "soma") == 0) {
        printf(BOLD "Função: sum / soma (Soma)\n" RESET);
        printf("Sintaxe: sum(val1, val2, ...) ou soma(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para somar\n");
        printf("Retorna: Soma total dos valores\n");
        printf("Exemplo: sum(1, 2, 3, 4) retorna 10\n");
        printf("Exemplo: soma(10, 20, 30) retorna 60\n");
        printf("Aplicação: Totais de vendas, custos, inventários\n");
    }
    else if (strcmp(function_name, "min") == 0 || strcmp(function_name, "minimo") == 0) {
        printf(BOLD "Função: min / minimo (Mínimo)\n" RESET);
        printf("Sintaxe: min(val1, val2, ...) ou minimo(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para encontrar o mínimo\n");
        printf("Retorna: Menor valor do conjunto\n");
        printf("Exemplo: min(5, 2, 8, 1) retorna 1\n");
        printf("Exemplo: minimo(3, 7, 2, 9) retorna 2\n");
        printf("Aplicação: Temperaturas mínimas, piores desempenhos\n");
    }
    else if (strcmp(function_name, "max") == 0 || strcmp(function_name, "maximo") == 0) {
        printf(BOLD "Função: max / maximo (Máximo)\n" RESET);
        printf("Sintaxe: max(val1, val2, ...) ou maximo(val1, val2, ...)\n");
        printf("Parâmetros: val1, val2, ... - números para encontrar o máximo\n");
        printf("Retorna: Maior valor do conjunto\n");
        printf("Exemplo: max(5, 2, 8, 1) retorna 8\n");
        printf("Exemplo: maximo(3, 7, 2, 9) retorna 9\n");
        printf("Aplicação: Temperaturas máximas, melhores desempenhos\n");
    }
    
    // FUNÇÕES FINANCEIRAS BÁSICAS
    else if (strcmp(function_name, "si") == 0 || strcmp(function_name, "js") == 0) {
        printf(BOLD "Função: si / js (Juros Simples)\n" RESET);
        printf("Sintaxe: si(principal, taxa, tempo) ou js(principal, taxa, tempo)\n");
        printf("Parâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\n");
        printf("Retorna: Valor dos juros simples\n");
        printf("Exemplo: si(1000, 0.05, 2) retorna 100\n");
        printf("Exemplo: js(500, 0.1, 3) retorna 150\n");
        printf("Aplicação: Empréstimos de curto prazo, investimentos simples\n");
    }
    else if (strcmp(function_name, "fv_si") == 0 || strcmp(function_name, "montante_js") == 0) {
        printf(BOLD "Função: fv_si / montante_js (Montante Juros Simples)\n" RESET);
        printf("Sintaxe: fv_si(principal, taxa, tempo) ou montante_js(principal, taxa, tempo)\n");
        printf("Parâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\n");
        printf("Retorna: Montante total (principal + juros)\n");
        printf("Exemplo: fv_si(1000, 0.05, 2) retorna 1100\n");
        printf("Exemplo: montante_js(500, 0.1, 3) retorna 650\n");
        printf("Aplicação: Cálculo de retorno de investimentos simples\n");
    }
    else if (strcmp(function_name, "ci") == 0 || strcmp(function_name, "jc") == 0) {
        printf(BOLD "Função: ci / jc (Juros Compostos)\n" RESET);
        printf("Sintaxe: ci(principal, taxa, tempo) ou jc(principal, taxa, tempo)\n");
        printf("Parâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\n");
        printf("Retorna: Valor dos juros compostos\n");
        printf("Exemplo: ci(1000, 0.05, 2) retorna 102.5\n");
        printf("Exemplo: jc(500, 0.1, 3) retorna 165.5\n");
        printf("Aplicação: Investimentos de longo prazo, poupança\n");
    }
    else if (strcmp(function_name, "fv_ci") == 0 || strcmp(function_name, "montante_jc") == 0) {
        printf(BOLD "Função: fv_ci / montante_jc (Montante Juros Compostos)\n" RESET);
        printf("Sintaxe: fv_ci(principal, taxa, tempo) ou montante_jc(principal, taxa, tempo)\n");
        printf("Parâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\n");
        printf("Retorna: Montante total com juros compostos\n");
        printf("Exemplo: fv_ci(1000, 0.05, 2) retorna 1102.5\n");
        printf("Exemplo: montante_jc(500, 0.1, 3) retorna 665.5\n");
        printf("Aplicação: Planejamento de aposentadoria, investimentos\n");
    }
    
    // FUNÇÕES FINANCEIRAS AVANÇADAS
    else if (strcmp(function_name, "pv") == 0 || strcmp(function_name, "vp") == 0) {
        printf(BOLD "Função: pv / vp (Valor Presente)\n" RESET);
        printf("Sintaxe: pv(taxa, períodos, pagamento) ou vp(taxa, períodos, pagamento)\n");
        printf("Parâmetros: taxa - juros por período, períodos - número de períodos, pagamento - valor do pagamento periódico\n");
        printf("Retorna: Valor presente da série de pagamentos\n");
        printf("Exemplo: pv(0.05, 10, 100) retorna ~-772.17\n");
        printf("Exemplo: vp(0.1, 5, 200) retorna ~-758.16\n");
        printf("Aplicação: Avaliação de investimentos, empréstimos\n");
    }
    else if (strcmp(function_name, "fv") == 0 || strcmp(function_name, "vf") == 0) {
        printf(BOLD "Função: fv / vf (Valor Futuro)\n" RESET);
        printf("Sintaxe: fv(taxa, períodos, pagamento) ou vf(taxa, períodos, pagamento)\n");
        printf("Parâmetros: taxa - juros por período, períodos - número de períodos, pagamento - valor do pagamento periódico\n");
        printf("Retorna: Valor futuro da série de pagamentos\n");
        printf("Exemplo: fv(0.05, 10, 100) retorna ~-1257.79\n");
        printf("Exemplo: vf(0.1, 5, 200) retorna ~-1221.02\n");
        printf("Aplicação: Planejamento de poupança, aposentadoria\n");
    }
    else if (strcmp(function_name, "pmt") == 0 || strcmp(function_name, "pagamento") == 0) {
        printf(BOLD "Função: pmt / pagamento (Pagamento Periódico)\n" RESET);
        printf("Sintaxe: pmt(taxa, períodos, valor_presente) ou pagamento(taxa, períodos, valor_presente)\n");
        printf("Parâmetros: taxa - juros por período, períodos - número de períodos, valor_presente - valor do empréstimo/investimento\n");
        printf("Retorna: Valor do pagamento periódico\n");
        printf("Exemplo: pmt(0.05, 10, 1000) retorna ~-129.50\n");
        printf("Exemplo: pagamento(0.1, 5, 500) retorna ~-131.90\n");
        printf("Aplicação: Cálculo de prestações, parcelas\n");
    }
    else if (strcmp(function_name, "nper") == 0 || strcmp(function_name, "periodos") == 0) {
        printf(BOLD "Função: nper / periodos (Número de Períodos)\n" RESET);
        printf("Sintaxe: nper(taxa, pagamento, valor_presente) ou periodos(taxa, pagamento, valor_presente)\n");
        printf("Parâmetros: taxa - juros por período, pagamento - valor do pagamento periódico, valor_presente - valor do empréstimo/investimento\n");
        printf("Retorna: Número de períodos necessários\n");
        printf("Exemplo: nper(0.05, 200, 1000) retorna ~-5.90\n");
        printf("Exemplo: periodos(0.1, 400, 1000) retorna ~-3.02\n");
        printf("Aplicação: Planejamento de quitação de dívidas\n");
    }
    else if (strcmp(function_name, "rate") == 0 || strcmp(function_name, "taxa") == 0) {
        printf(BOLD "Função: rate / taxa (Taxa de Juros)\n" RESET);
        printf("Sintaxe: rate(períodos, pagamento, valor_presente, valor_futuro) ou taxa(períodos, pagamento, valor_presente, valor_futuro)\n");
        printf("Parâmetros: períodos - número de períodos, pagamento - valor do pagamento periódico, valor_presente - valor inicial, valor_futuro - valor final\n");
        printf("Retorna: Taxa de juros implícita\n");
        printf("Exemplo: rate(10, 100, 1000, 0) retorna ~0.05\n");
        printf("Exemplo: taxa(5, 200, 1000, 0) retorna ~0.05\n");
        printf("Aplicação: Análise de retorno de investimentos\n");
    }
    else if (strcmp(function_name, "npv") == 0 || strcmp(function_name, "vpl") == 0) {
        printf(BOLD "Função: npv / vpl (Valor Presente Líquido)\n" RESET);
        printf("Sintaxe: npv(taxa, fluxo1, fluxo2, ...) ou vpl(taxa, fluxo1, fluxo2, ...)\n");
        printf("Parâmetros: taxa - taxa de desconto, fluxo1, fluxo2, ... - fluxos de caixa (negativo para investimento)\n");
        printf("Retorna: Valor presente líquido dos fluxos de caixa\n");
        printf("Exemplo: npv(0.1, -1000, 300, 400, 500) retorna ~49.21\n");
        printf("Exemplo: vpl(0.05, -500, 200, 200, 200) retorna ~44.65\n");
        printf("Aplicação: Avaliação de projetos de investimento\n");
    }
    else if (strcmp(function_name, "irr") == 0 || strcmp(function_name, "tir") == 0) {
        printf(BOLD "Função: irr / tir (Taxa Interna de Retorno)\n" RESET);
        printf("Sintaxe: irr(fluxo1, fluxo2, ...) ou tir(fluxo1, fluxo2, ...)\n");
        printf("Parâmetros: fluxo1, fluxo2, ... - fluxos de caixa (negativo para investimento)\n");
        printf("Retorna: Taxa interna de retorno do investimento\n");
        printf("Exemplo: irr(-1000, 300, 400, 500) retorna ~0.089\n");
        printf("Exemplo: tir(-500, 200, 200, 200) retorna ~0.097\n");
        printf("Aplicação: Comparação de rentabilidade de projetos\n");
    }
    else {
        printf(ERROR_COLOR "Função '%s' não encontrada.\n" RESET, function_name);
        printf("Digite " BOLD "help" RESET " para ver lista de funções disponíveis.\n");
    }
}

int get_total_help_pages() {
    return 3;
}

void print_help_page(int page) {
    print_help_header();
    printf("\n" BOLD "Página %d de %d\n\n" RESET, page, get_total_help_pages());
    
    switch (page) {
        case 1:
            printf(BOLD "=== OPERADORES MATEMÁTICOS ===\n\n" RESET);
            printf(BOLD "+" RESET "     Adição: a + b\n");
            printf(BOLD "-" RESET "     Subtração: a - b\n");
            printf(BOLD "*" RESET "     Multiplicação: a * b\n");
            printf(BOLD "/" RESET "     Divisão: a / b\n");
            printf(BOLD "%%" RESET "     Módulo: a %% b (resto da divisão)\n");
            printf(BOLD "^" RESET "     Potência: a ^ b\n");
            printf(BOLD "!" RESET "     Fatorial: a! (inteiros não-negativos)\n");
            
            printf("\n" BOLD "=== FUNÇÕES MATEMÁTICAS ===\n\n" RESET);
            printf(BOLD "sqrt, raiz" RESET "    Raiz quadrada\n");
            printf(BOLD "sin, sen" RESET "      Seno (radianos)\n");
            printf(BOLD "cos" RESET "           Cosseno (radianos)\n");
            printf(BOLD "tan" RESET "           Tangente (radianos)\n");
            printf(BOLD "log, log10" RESET "    Logaritmo base 10\n");
            printf(BOLD "ln" RESET "            Logaritmo natural\n");
            printf(BOLD "exp" RESET "           Exponencial (e^x)\n");
            printf(BOLD "abs" RESET "           Valor absoluto\n");
            break;
            
        case 2:
            printf(BOLD "=== FUNÇÕES ESTATÍSTICAS ===\n\n" RESET);
            printf(BOLD "mean, media" RESET "       Média aritmética\n");
            printf(BOLD "median, mediana" RESET "   Mediana\n");
            printf(BOLD "std, desvio" RESET "       Desvio padrão\n");
            printf(BOLD "variance, variancia" RESET " Variância\n");
            printf(BOLD "mode, moda" RESET "        Moda (valor mais frequente)\n");
            printf(BOLD "sum, soma" RESET "         Soma total\n");
            printf(BOLD "min, minimo" RESET "       Valor mínimo\n");
            printf(BOLD "max, maximo" RESET "       Valor máximo\n");
            
            printf("\n" BOLD "=== FUNÇÕES FINANCEIRAS BÁSICAS ===\n\n" RESET);
            printf(BOLD "si, js" RESET "              Juros simples\n");
            printf(BOLD "fv_si, montante_js" RESET "  Montante juros simples\n");
            printf(BOLD "ci, jc" RESET "              Juros compostos\n");
            printf(BOLD "fv_ci, montante_jc" RESET "  Montante juros compostos\n");
            break;
            
        case 3:
            printf(BOLD "=== FUNÇÕES FINANCEIRAS AVANÇADAS ===\n\n" RESET);
            printf(BOLD "pv, vp" RESET "           Valor presente\n");
            printf(BOLD "fv, vf" RESET "           Valor futuro\n");
            printf(BOLD "pmt, pagamento" RESET "   Pagamento periódico\n");
            printf(BOLD "nper, periodos" RESET "   Número de períodos\n");
            printf(BOLD "rate, taxa" RESET "       Taxa de juros\n");
            printf(BOLD "npv, vpl" RESET "         Valor presente líquido\n");
            printf(BOLD "irr, tir" RESET "         Taxa interna de retorno\n");
            
            printf("\n" BOLD "=== USO PRÁTICO ===\n\n" RESET);
            printf("Para ajuda detalhada de uma função:\n");
            printf("  " BOLD "help sqrt" RESET "     - Mostra ajuda da função sqrt\n");
            printf("  " BOLD "help media" RESET "    - Mostra ajuda da função mean\n");
            printf("  " BOLD "help vpl" RESET "      - Mostra ajuda da função npv\n");
            break;
            
        default:
            printf(ERROR_COLOR "Página %d não existe.\n" RESET, page);
            printf("Páginas disponíveis: 1 a %d\n", get_total_help_pages());
            return;
    }
    
    printf("\n" CYAN "Digite 'help <número>' para navegar ou 'help <função>' para detalhes.\n" RESET);
}
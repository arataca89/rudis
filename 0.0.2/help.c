#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "help.h"
#include "lang.h"

#define LINES_PER_PAGE 20

// =============================================================================
// FUNÇÕES DE TRADUÇÃO - GERAL
// =============================================================================

const char* get_help_header() {
    return (current_lang == LANG_PT) 
        ? "=== RUDIS 0.0.1 - SISTEMA DE AJUDA ==="
        : "=== RUDIS 0.0.1 - HELP SYSTEM ===";
}

const char* get_help_commands_title() {
    return (current_lang == LANG_PT) 
        ? "COMANDOS DO SISTEMA:"
        : "SYSTEM COMMANDS:";
}

const char* get_help_categories_title() {
    return (current_lang == LANG_PT) 
        ? "CATEGORIAS DE FUNÇÕES:"
        : "FUNCTION CATEGORIES:";
}

const char* get_help_examples_title() {
    return (current_lang == LANG_PT) 
        ? "EXEMPLOS RÁPIDOS:"
        : "QUICK EXAMPLES:";
}

const char* get_help_more_help() {
    return (current_lang == LANG_PT) 
        ? "\nDigite 'help 1' para lista completa de funções."
        : "\nType 'help 1' for complete function list.";
}

const char* get_help_function_not_found(const char* function_name) {
    static char buffer[200];
    if (current_lang == LANG_PT) {
        snprintf(buffer, sizeof(buffer), 
                 "Função '%s' não encontrada.\nDigite 'help' para ver lista de funções disponíveis.", 
                 function_name);
    } else {
        snprintf(buffer, sizeof(buffer), 
                 "Function '%s' not found.\nType 'help' to see available functions list.", 
                 function_name);
    }
    return buffer;
}

const char* get_help_page_navigation() {
    return (current_lang == LANG_PT) 
        ? "\nDigite 'help <número>' para navegar ou 'help <função>' para detalhes."
        : "\nType 'help <number>' to navigate or 'help <function>' for details.";
}

const char* get_help_invalid_page(int page, int total_pages) {
    static char buffer[100];
    if (current_lang == LANG_PT) {
        snprintf(buffer, sizeof(buffer), 
                 "Página %d não existe.\nPáginas disponíveis: 1 a %d", 
                 page, total_pages);
    } else {
        snprintf(buffer, sizeof(buffer), 
                 "Page %d does not exist.\nAvailable pages: 1 to %d", 
                 page, total_pages);
    }
    return buffer;
}

// =============================================================================
// TRADUÇÕES PARA OPERADORES
// =============================================================================

const char* get_help_operator_add() {
    return (current_lang == LANG_PT) 
        ? "Operador: + (Adição)\nSintaxe: a + b\nDescrição: Soma dois valores numéricos.\nExemplo: 5 + 3 retorna 8"
        : "Operator: + (Addition)\nSyntax: a + b\nDescription: Adds two numeric values.\nExample: 5 + 3 returns 8";
}

const char* get_help_operator_sub() {
    return (current_lang == LANG_PT) 
        ? "Operador: - (Subtração)\nSintaxe: a - b\nDescrição: Subtrai o segundo valor do primeiro.\nExemplo: 10 - 4 retorna 6"
        : "Operator: - (Subtraction)\nSyntax: a - b\nDescription: Subtracts second value from first.\nExample: 10 - 4 returns 6";
}

const char* get_help_operator_mul() {
    return (current_lang == LANG_PT) 
        ? "Operador: * (Multiplicação)\nSintaxe: a * b\nDescrição: Multiplica dois valores.\nExemplo: 6 * 7 retorna 42"
        : "Operator: * (Multiplication)\nSyntax: a * b\nDescription: Multiplies two values.\nExample: 6 * 7 returns 42";
}

const char* get_help_operator_div() {
    return (current_lang == LANG_PT) 
        ? "Operador: / (Divisão)\nSintaxe: a / b\nDescrição: Divide o primeiro valor pelo segundo.\nExemplo: 15 / 3 retorna 5\nNota: Retorna erro se b = 0"
        : "Operator: / (Division)\nSyntax: a / b\nDescription: Divides first value by second.\nExample: 15 / 3 returns 5\nNote: Returns error if b = 0";
}

const char* get_help_operator_mod() {
    return (current_lang == LANG_PT) 
        ? "Operador: %% (Módulo)\nSintaxe: a %% b\nDescrição: Retorna o resto da divisão inteira.\nExemplo: 10 %% 3 retorna 1"
        : "Operator: %% (Modulo)\nSyntax: a %% b\nDescription: Returns remainder of integer division.\nExample: 10 %% 3 returns 1";
}

const char* get_help_operator_pow() {
    return (current_lang == LANG_PT) 
        ? "Operador: ^ (Potência)\nSintaxe: a ^ b\nDescrição: Eleva a à potência de b.\nExemplo: 2 ^ 8 retorna 256"
        : "Operator: ^ (Power)\nSyntax: a ^ b\nDescription: Raises a to the power of b.\nExample: 2 ^ 8 returns 256";
}

const char* get_help_operator_fact() {
    return (current_lang == LANG_PT) 
        ? "Operador: ! (Fatorial)\nSintaxe: a!\nDescrição: Calcula o fatorial de um número inteiro.\nExemplo: 5! retorna 120\nNota: Funciona apenas com inteiros não-negativos"
        : "Operator: ! (Factorial)\nSyntax: a!\nDescription: Calculates factorial of an integer.\nExample: 5! returns 120\nNote: Works only with non-negative integers";
}

// =============================================================================
// TRADUÇÕES PARA FUNÇÕES MATEMÁTICAS
// =============================================================================

const char* get_help_function_sqrt() {
    return (current_lang == LANG_PT) 
        ? "Função: sqrt / raiz (Raiz Quadrada)\nSintaxe: sqrt(x) ou raiz(x)\nParâmetros: x - número não negativo\nRetorna: Raiz quadrada de x\nExemplo: sqrt(25) retorna 5\nExemplo: raiz(16) retorna 4\nAplicação: Cálculo de distâncias, áreas, desvio padrão"
        : "Function: sqrt / raiz (Square Root)\nSyntax: sqrt(x) or raiz(x)\nParameters: x - non-negative number\nReturns: Square root of x\nExample: sqrt(25) returns 5\nExample: raiz(16) returns 4\nApplication: Distance calculation, areas, standard deviation";
}

const char* get_help_function_sin() {
    return (current_lang == LANG_PT) 
        ? "Função: sin / sen (Seno)\nSintaxe: sin(x) ou sen(x)\nParâmetros: x - ângulo em radianos\nRetorna: Seno do ângulo x\nExemplo: sin(0) retorna 0\nExemplo: sen(1.5708) retorna ~1 (π/2)\nAplicação: Ondas, oscilações, processamento de sinais"
        : "Function: sin / sen (Sine)\nSyntax: sin(x) or sen(x)\nParameters: x - angle in radians\nReturns: Sine of angle x\nExample: sin(0) returns 0\nExample: sen(1.5708) returns ~1 (π/2)\nApplication: Waves, oscillations, signal processing";
}

const char* get_help_function_cos() {
    return (current_lang == LANG_PT) 
        ? "Função: cos (Cosseno)\nSintaxe: cos(x)\nParâmetros: x - ângulo em radianos\nRetorna: Cosseno do ângulo x\nExemplo: cos(0) retorna 1\nExemplo: cos(3.1416) retorna ~-1 (π)\nAplicação: Movimento harmônico, rotações"
        : "Function: cos (Cosine)\nSyntax: cos(x)\nParameters: x - angle in radians\nReturns: Cosine of angle x\nExample: cos(0) returns 1\nExample: cos(3.1416) returns ~-1 (π)\nApplication: Harmonic motion, rotations";
}

const char* get_help_function_tan() {
    return (current_lang == LANG_PT) 
        ? "Função: tan (Tangente)\nSintaxe: tan(x)\nParâmetros: x - ângulo em radianos\nRetorna: Tangente do ângulo x\nExemplo: tan(0) retorna 0\nExemplo: tan(0.7854) retorna ~1 (π/4)\nAplicação: Triângulos, inclinações, sombras"
        : "Function: tan (Tangent)\nSyntax: tan(x)\nParameters: x - angle in radians\nReturns: Tangent of angle x\nExample: tan(0) returns 0\nExample: tan(0.7854) returns ~1 (π/4)\nApplication: Triangles, slopes, shadows";
}

const char* get_help_function_log() {
    return (current_lang == LANG_PT) 
        ? "Função: log / log10 (Logaritmo Base 10)\nSintaxe: log(x) ou log10(x)\nParâmetros: x - número positivo\nRetorna: Logaritmo base 10 de x\nExemplo: log(100) retorna 2\nExemplo: log10(1000) retorna 3\nAplicação: Escalas logarítmicas, pH, decibéis"
        : "Function: log / log10 (Base 10 Logarithm)\nSyntax: log(x) or log10(x)\nParameters: x - positive number\nReturns: Base 10 logarithm of x\nExample: log(100) returns 2\nExample: log10(1000) returns 3\nApplication: Logarithmic scales, pH, decibels";
}

const char* get_help_function_ln() {
    return (current_lang == LANG_PT) 
        ? "Função: ln (Logaritmo Natural)\nSintaxe: ln(x)\nParâmetros: x - número positivo\nRetorna: Logaritmo natural de x (base e)\nExemplo: ln(2.71828) retorna ~1\nAplicação: Crescimento contínuo, juros compostos"
        : "Function: ln (Natural Logarithm)\nSyntax: ln(x)\nParameters: x - positive number\nReturns: Natural logarithm of x (base e)\nExample: ln(2.71828) returns ~1\nApplication: Continuous growth, compound interest";
}

const char* get_help_function_exp() {
    return (current_lang == LANG_PT) 
        ? "Função: exp (Exponencial)\nSintaxe: exp(x)\nParâmetros: x - expoente\nRetorna: e elevado a x\nExemplo: exp(1) retorna ~2.71828\nExemplo: exp(0) retorna 1\nAplicação: Crescimento exponencial, decaimento"
        : "Function: exp (Exponential)\nSyntax: exp(x)\nParameters: x - exponent\nReturns: e raised to x\nExample: exp(1) returns ~2.71828\nExample: exp(0) returns 1\nApplication: Exponential growth, decay";
}

const char* get_help_function_abs() {
    return (current_lang == LANG_PT) 
        ? "Função: abs (Valor Absoluto)\nSintaxe: abs(x)\nParâmetros: x - qualquer número\nRetorna: Valor absoluto de x\nExemplo: abs(-5.5) retorna 5.5\nExemplo: abs(10) retorna 10\nAplicação: Distâncias, erros absolutos, magnitude"
        : "Function: abs (Absolute Value)\nSyntax: abs(x)\nParameters: x - any number\nReturns: Absolute value of x\nExample: abs(-5.5) returns 5.5\nExample: abs(10) returns 10\nApplication: Distances, absolute errors, magnitude";
}

// =============================================================================
// TRADUÇÕES PARA FUNÇÕES ESTATÍSTICAS
// =============================================================================

const char* get_help_function_mean() {
    return (current_lang == LANG_PT) 
        ? "Função: mean / media (Média Aritmética)\nSintaxe: mean(val1, val2, ...) ou media(val1, val2, ...)\nParâmetros: val1, val2, ... - números para calcular a média\nRetorna: Média dos valores fornecidos\nExemplo: mean(1, 2, 3, 4, 5) retorna 3\nExemplo: media(10, 20, 30) retorna 20\nAplicação: Notas médias, gastos médios, desempenho"
        : "Function: mean / media (Arithmetic Mean)\nSyntax: mean(val1, val2, ...) or media(val1, val2, ...)\nParameters: val1, val2, ... - numbers to calculate mean\nReturns: Mean of provided values\nExample: mean(1, 2, 3, 4, 5) returns 3\nExample: media(10, 20, 30) returns 20\nApplication: Average grades, average expenses, performance";
}

const char* get_help_function_median() {
    return (current_lang == LANG_PT) 
        ? "Função: median / mediana (Mediana)\nSintaxe: median(val1, val2, ...) ou mediana(val1, val2, ...)\nParâmetros: val1, val2, ... - números para calcular a mediana\nRetorna: Valor do meio dos dados ordenados\nExemplo: median(1, 3, 5) retorna 3\nExemplo: mediana(1, 2, 3, 4) retorna 2.5\nAplicação: Análise de renda, preços, dados com outliers"
        : "Function: median / mediana (Median)\nSyntax: median(val1, val2, ...) or mediana(val1, val2, ...)\nParameters: val1, val2, ... - numbers to calculate median\nReturns: Middle value of sorted data\nExample: median(1, 3, 5) returns 3\nExample: mediana(1, 2, 3, 4) returns 2.5\nApplication: Income analysis, prices, data with outliers";
}

const char* get_help_function_std() {
    return (current_lang == LANG_PT) 
        ? "Função: std / desvio (Desvio Padrão)\nSintaxe: std(val1, val2, ...) ou desvio(val1, val2, ...)\nParâmetros: val1, val2, ... - números para calcular o desvio\nRetorna: Desvio padrão amostral dos valores\nExemplo: std(10, 20) retorna ~7.07\nExemplo: desvio(5, 5, 5) retorna 0\nAplicação: Volatilidade, controle de qualidade, risco"
        : "Function: std / desvio (Standard Deviation)\nSyntax: std(val1, val2, ...) or desvio(val1, val2, ...)\nParameters: val1, val2, ... - numbers to calculate deviation\nReturns: Sample standard deviation of values\nExample: std(10, 20) returns ~7.07\nExample: desvio(5, 5, 5) returns 0\nApplication: Volatility, quality control, risk";
}

const char* get_help_function_variance() {
    return (current_lang == LANG_PT) 
        ? "Função: variance / variancia (Variância)\nSintaxe: variance(val1, val2, ...) ou variancia(val1, val2, ...)\nParâmetros: val1, val2, ... - números para calcular a variância\nRetorna: Variância amostral dos valores\nExemplo: variance(1, 2, 3) retorna 1\nExemplo: variancia(5, 10, 15) retorna 25\nAplicação: Análise de risco, dispersão de dados"
        : "Function: variance / variancia (Variance)\nSyntax: variance(val1, val2, ...) or variancia(val1, val2, ...)\nParameters: val1, val2, ... - numbers to calculate variance\nReturns: Sample variance of values\nExample: variance(1, 2, 3) returns 1\nExample: variancia(5, 10, 15) returns 25\nApplication: Risk analysis, data dispersion";
}

const char* get_help_function_mode() {
    return (current_lang == LANG_PT) 
        ? "Função: mode / moda (Moda)\nSintaxe: mode(val1, val2, ...) ou moda(val1, val2, ...)\nParâmetros: val1, val2, ... - números para encontrar a moda\nRetorna: Valor mais frequente no conjunto\nExemplo: mode(1, 1, 2, 2, 2, 3) retorna 2\nExemplo: moda(5, 5, 10, 10, 10) retorna 10\nAplicação: Pesquisas de preferência, produtos mais vendidos"
        : "Function: mode / moda (Mode)\nSyntax: mode(val1, val2, ...) or moda(val1, val2, ...)\nParameters: val1, val2, ... - numbers to find mode\nReturns: Most frequent value in the set\nExample: mode(1, 1, 2, 2, 2, 3) returns 2\nExample: moda(5, 5, 10, 10, 10) returns 10\nApplication: Preference surveys, best-selling products";
}

const char* get_help_function_sum() {
    return (current_lang == LANG_PT) 
        ? "Função: sum / soma (Soma)\nSintaxe: sum(val1, val2, ...) ou soma(val1, val2, ...)\nParâmetros: val1, val2, ... - números para somar\nRetorna: Soma total dos valores\nExemplo: sum(1, 2, 3, 4) retorna 10\nExemplo: soma(10, 20, 30) retorna 60\nAplicação: Totais de vendas, custos, inventários"
        : "Function: sum / soma (Sum)\nSyntax: sum(val1, val2, ...) or soma(val1, val2, ...)\nParameters: val1, val2, ... - numbers to sum\nReturns: Total sum of values\nExample: sum(1, 2, 3, 4) returns 10\nExample: soma(10, 20, 30) returns 60\nApplication: Sales totals, costs, inventories";
}

const char* get_help_function_min() {
    return (current_lang == LANG_PT) 
        ? "Função: min / minimo (Mínimo)\nSintaxe: min(val1, val2, ...) ou minimo(val1, val2, ...)\nParâmetros: val1, val2, ... - números para encontrar o mínimo\nRetorna: Menor valor do conjunto\nExemplo: min(5, 2, 8, 1) retorna 1\nExemplo: minimo(3, 7, 2, 9) retorna 2\nAplicação: Temperaturas mínimas, piores desempenhos"
        : "Function: min / minimo (Minimum)\nSyntax: min(val1, val2, ...) or minimo(val1, val2, ...)\nParameters: val1, val2, ... - numbers to find minimum\nReturns: Smallest value in the set\nExample: min(5, 2, 8, 1) returns 1\nExample: minimo(3, 7, 2, 9) returns 2\nApplication: Minimum temperatures, worst performances";
}

const char* get_help_function_max() {
    return (current_lang == LANG_PT) 
        ? "Função: max / maximo (Máximo)\nSintaxe: max(val1, val2, ...) ou maximo(val1, val2, ...)\nParâmetros: val1, val2, ... - números para encontrar o máximo\nRetorna: Maior valor do conjunto\nExemplo: max(5, 2, 8, 1) retorna 8\nExemplo: maximo(3, 7, 2, 9) retorna 9\nAplicação: Temperaturas máximas, melhores desempenhos"
        : "Function: max / maximo (Maximum)\nSyntax: max(val1, val2, ...) or maximo(val1, val2, ...)\nParameters: val1, val2, ... - numbers to find maximum\nReturns: Largest value in the set\nExample: max(5, 2, 8, 1) returns 8\nExample: maximo(3, 7, 2, 9) returns 9\nApplication: Maximum temperatures, best performances";
}

// =============================================================================
// TRADUÇÕES PARA FUNÇÕES FINANCEIRAS
// =============================================================================

const char* get_help_function_si() {
    return (current_lang == LANG_PT) 
        ? "Função: si / js (Juros Simples)\nSintaxe: si(principal, taxa, tempo) ou js(principal, taxa, tempo)\nParâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\nRetorna: Valor dos juros simples\nExemplo: si(1000, 0.05, 2) retorna 100\nExemplo: js(500, 0.1, 3) retorna 150\nAplicação: Empréstimos de curto prazo, investimentos simples"
        : "Function: si / js (Simple Interest)\nSyntax: si(principal, rate, time) or js(principal, rate, time)\nParameters: principal - initial value, rate - interest per period, time - number of periods\nReturns: Simple interest value\nExample: si(1000, 0.05, 2) returns 100\nExample: js(500, 0.1, 3) returns 150\nApplication: Short-term loans, simple investments";
}

const char* get_help_function_fv_si() {
    return (current_lang == LANG_PT) 
        ? "Função: fv_si / montante_js (Montante Juros Simples)\nSintaxe: fv_si(principal, taxa, tempo) ou montante_js(principal, taxa, tempo)\nParâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\nRetorna: Montante total (principal + juros)\nExemplo: fv_si(1000, 0.05, 2) retorna 1100\nExemplo: montante_js(500, 0.1, 3) retorna 650\nAplicação: Cálculo de retorno de investimentos simples"
        : "Function: fv_si / montante_js (Simple Interest Amount)\nSyntax: fv_si(principal, rate, time) or montante_js(principal, rate, time)\nParameters: principal - initial value, rate - interest per period, time - number of periods\nReturns: Total amount (principal + interest)\nExample: fv_si(1000, 0.05, 2) returns 1100\nExample: montante_js(500, 0.1, 3) returns 650\nApplication: Return calculation for simple investments";
}

const char* get_help_function_ci() {
    return (current_lang == LANG_PT) 
        ? "Função: ci / jc (Juros Compostos)\nSintaxe: ci(principal, taxa, tempo) ou jc(principal, taxa, tempo)\nParâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\nRetorna: Valor dos juros compostos\nExemplo: ci(1000, 0.05, 2) retorna 102.5\nExemplo: jc(500, 0.1, 3) retorna 165.5\nAplicação: Investimentos de longo prazo, poupança"
        : "Function: ci / jc (Compound Interest)\nSyntax: ci(principal, rate, time) or jc(principal, rate, time)\nParameters: principal - initial value, rate - interest per period, time - number of periods\nReturns: Compound interest value\nExample: ci(1000, 0.05, 2) returns 102.5\nExample: jc(500, 0.1, 3) returns 165.5\nApplication: Long-term investments, savings";
}

const char* get_help_function_fv_ci() {
    return (current_lang == LANG_PT) 
        ? "Função: fv_ci / montante_jc (Montante Juros Compostos)\nSintaxe: fv_ci(principal, taxa, tempo) ou montante_jc(principal, taxa, tempo)\nParâmetros: principal - valor inicial, taxa - juros por período, tempo - número de períodos\nRetorna: Montante total com juros compostos\nExemplo: fv_ci(1000, 0.05, 2) retorna 1102.5\nExemplo: montante_jc(500, 0.1, 3) retorna 665.5\nAplicação: Planejamento de aposentadoria, investimentos"
        : "Function: fv_ci / montante_jc (Compound Interest Amount)\nSyntax: fv_ci(principal, rate, time) or montante_jc(principal, rate, time)\nParameters: principal - initial value, rate - interest per period, time - number of periods\nReturns: Total amount with compound interest\nExample: fv_ci(1000, 0.05, 2) returns 1102.5\nExample: montante_jc(500, 0.1, 3) returns 665.5\nApplication: Retirement planning, investments";
}

const char* get_help_function_pv() {
    return (current_lang == LANG_PT) 
        ? "Função: pv / vp (Valor Presente)\nSintaxe: pv(taxa, períodos, pagamento) ou vp(taxa, períodos, pagamento)\nParâmetros: taxa - juros por período, períodos - número de períodos, pagamento - valor do pagamento periódico\nRetorna: Valor presente da série de pagamentos\nExemplo: pv(0.05, 10, 100) retorna ~-772.17\nExemplo: vp(0.1, 5, 200) retorna ~-758.16\nAplicação: Avaliação de investimentos, empréstimos"
        : "Function: pv / vp (Present Value)\nSyntax: pv(rate, periods, payment) or vp(rate, periods, payment)\nParameters: rate - interest per period, periods - number of periods, payment - periodic payment value\nReturns: Present value of payment series\nExample: pv(0.05, 10, 100) returns ~-772.17\nExample: vp(0.1, 5, 200) returns ~-758.16\nApplication: Investment evaluation, loans";
}

const char* get_help_function_fv() {
    return (current_lang == LANG_PT) 
        ? "Função: fv / vf (Valor Futuro)\nSintaxe: fv(taxa, períodos, pagamento) ou vf(taxa, períodos, pagamento)\nParâmetros: taxa - juros por período, períodos - número de períodos, pagamento - valor do pagamento periódico\nRetorna: Valor futuro da série de pagamentos\nExemplo: fv(0.05, 10, 100) retorna ~-1257.79\nExemplo: vf(0.1, 5, 200) retorna ~-1221.02\nAplicação: Planejamento de poupança, aposentadoria"
        : "Function: fv / vf (Future Value)\nSyntax: fv(rate, periods, payment) or vf(rate, periods, payment)\nParameters: rate - interest per period, periods - number of periods, payment - periodic payment value\nReturns: Future value of payment series\nExample: fv(0.05, 10, 100) returns ~-1257.79\nExample: vf(0.1, 5, 200) returns ~-1221.02\nApplication: Savings planning, retirement";
}

const char* get_help_function_pmt() {
    return (current_lang == LANG_PT) 
        ? "Função: pmt / pagamento (Pagamento Periódico)\nSintaxe: pmt(taxa, períodos, valor_presente) ou pagamento(taxa, períodos, valor_presente)\nParâmetros: taxa - juros por período, períodos - número de períodos, valor_presente - valor do empréstimo/investimento\nRetorna: Valor do pagamento periódico\nExemplo: pmt(0.05, 10, 1000) retorna ~-129.50\nExemplo: pagamento(0.1, 5, 500) retorna ~-131.90\nAplicação: Cálculo de prestações, parcelas"
        : "Function: pmt / pagamento (Periodic Payment)\nSyntax: pmt(rate, periods, present_value) or pagamento(rate, periods, present_value)\nParameters: rate - interest per period, periods - number of periods, present_value - loan/investment value\nReturns: Periodic payment value\nExample: pmt(0.05, 10, 1000) returns ~-129.50\nExample: pagamento(0.1, 5, 500) returns ~-131.90\nApplication: Installment calculation, payments";
}

const char* get_help_function_nper() {
    return (current_lang == LANG_PT) 
        ? "Função: nper / periodos (Número de Períodos)\nSintaxe: nper(taxa, pagamento, valor_presente) ou periodos(taxa, pagamento, valor_presente)\nParâmetros: taxa - juros por período, pagamento - valor do pagamento periódico, valor_presente - valor do empréstimo/investimento\nRetorna: Número de períodos necessários\nExemplo: nper(0.05, 200, 1000) retorna ~-5.90\nExemplo: periodos(0.1, 400, 1000) retorna ~-3.02\nAplicação: Planejamento de quitação de dívidas"
        : "Function: nper / periodos (Number of Periods)\nSyntax: nper(rate, payment, present_value) or periodos(rate, payment, present_value)\nParameters: rate - interest per period, payment - periodic payment value, present_value - loan/investment value\nReturns: Number of periods required\nExample: nper(0.05, 200, 1000) returns ~-5.90\nExample: periodos(0.1, 400, 1000) returns ~-3.02\nApplication: Debt repayment planning";
}

const char* get_help_function_rate() {
    return (current_lang == LANG_PT) 
        ? "Função: rate / taxa (Taxa de Juros)\nSintaxe: rate(períodos, pagamento, valor_presente, valor_futuro) ou taxa(períodos, pagamento, valor_presente, valor_futuro)\nParâmetros: períodos - número de períodos, pagamento - valor do pagamento periódico, valor_presente - valor inicial, valor_futuro - valor final\nRetorna: Taxa de juros implícita\nExemplo: rate(10, 100, 1000, 0) retorna ~0.05\nExemplo: taxa(5, 200, 1000, 0) retorna ~0.05\nAplicação: Análise de retorno de investimentos"
        : "Function: rate / taxa (Interest Rate)\nSyntax: rate(periods, payment, present_value, future_value) or taxa(periods, payment, present_value, future_value)\nParameters: periods - number of periods, payment - periodic payment value, present_value - initial value, future_value - final value\nReturns: Implicit interest rate\nExample: rate(10, 100, 1000, 0) returns ~0.05\nExample: taxa(5, 200, 1000, 0) returns ~0.05\nApplication: Investment return analysis";
}

const char* get_help_function_npv() {
    return (current_lang == LANG_PT) 
        ? "Função: npv / vpl (Valor Presente Líquido)\nSintaxe: npv(taxa, fluxo1, fluxo2, ...) ou vpl(taxa, fluxo1, fluxo2, ...)\nParâmetros: taxa - taxa de desconto, fluxo1, fluxo2, ... - fluxos de caixa (negativo para investimento)\nRetorna: Valor presente líquido dos fluxos de caixa\nExemplo: npv(0.1, -1000, 300, 400, 500) retorna ~49.21\nExemplo: vpl(0.05, -500, 200, 200, 200) retorna ~44.65\nAplicação: Avaliação de projetos de investimento"
        : "Function: npv / vpl (Net Present Value)\nSyntax: npv(rate, flow1, flow2, ...) or vpl(rate, flow1, flow2, ...)\nParameters: rate - discount rate, flow1, flow2, ... - cash flows (negative for investment)\nReturns: Net present value of cash flows\nExample: npv(0.1, -1000, 300, 400, 500) returns ~49.21\nExample: vpl(0.05, -500, 200, 200, 200) returns ~44.65\nApplication: Investment project evaluation";
}

const char* get_help_function_irr() {
    return (current_lang == LANG_PT) 
        ? "Função: irr / tir (Taxa Interna de Retorno)\nSintaxe: irr(fluxo1, fluxo2, ...) ou tir(fluxo1, fluxo2, ...)\nParâmetros: fluxo1, fluxo2, ... - fluxos de caixa (negativo para investimento)\nRetorna: Taxa interna de retorno do investimento\nExemplo: irr(-1000, 300, 400, 500) retorna ~0.089\nExemplo: tir(-500, 200, 200, 200) retorna ~0.097\nAplicação: Comparação de rentabilidade de projetos"
        : "Function: irr / tir (Internal Rate of Return)\nSyntax: irr(flow1, flow2, ...) or tir(flow1, flow2, ...)\nParameters: flow1, flow2, ... - cash flows (negative for investment)\nReturns: Internal rate of return of investment\nExample: irr(-1000, 300, 400, 500) returns ~0.089\nExample: tir(-500, 200, 200, 200) returns ~0.097\nApplication: Project profitability comparison";
}

// =============================================================================
// TRADUÇÕES PARA FUNÇÕES DE CONFIGURAÇÃO
// =============================================================================
const char* get_help_function_setdec() {
    return (current_lang == LANG_PT) 
        ? "Função: setdec (Configurar Casas Decimais)\nSintaxe: setdec(n)\nParâmetros: n - número de casas decimais (0-15)\nRetorna: 0 em caso de sucesso\nExemplo: setdec(2) - configura 2 casas decimais\nAplicação: Controle de precisão para dinheiro, ciência, etc."
        : "Function: setdec (Set Decimal Places)\nSyntax: setdec(n)\nParameters: n - number of decimal places (0-15)\nReturns: 0 on success\nExample: setdec(2) - sets 2 decimal places\nApplication: Precision control for money, science, etc.";
}

// =============================================================================
// FUNÇÕES PRINCIPAIS DE AJUDA 
// =============================================================================

void print_help_header() {
    printf(INFO_COLOR "%s\n" RESET, get_help_header());
}

void print_general_help() {
    print_help_header();
    printf("\n" BOLD "%s\n" RESET, get_help_commands_title());
    
    if (current_lang == LANG_PT) {
        printf("  help                    - Mostra esta ajuda geral\n");
        printf("  help <função>           - Ajuda específica de uma função\n");
        printf("  help <página>           - Navega pelas páginas de ajuda\n");
        printf("  exit, quit              - Sai do programa\n");
        printf("  set lang pt|en          - Muda o idioma\n");
        printf("  clear                   - Limpa a tela\n");
        printf("  vars                    - Lista variáveis definidas\n");
    } else {
        printf("  help                    - Shows this general help\n");
        printf("  help <function>         - Specific help for a function\n");
        printf("  help <page>             - Navigates through help pages\n");
        printf("  exit, quit              - Exits the program\n");
        printf("  set lang pt|en          - Changes language\n");
        printf("  clear                   - Clears screen\n");
        printf("  vars                    - Lists defined variables\n");
    }
    
    printf("\n" BOLD "%s\n" RESET, get_help_categories_title());
    
    if (current_lang == LANG_PT) {
        printf("  * Matemáticas Básicas     - +, -, *, /, %%, ^, !\n");
        printf("  * Funções Matemáticas     - sqrt, sin, cos, log, exp, abs\n");
        printf("  * Funções Estatísticas    - mean, median, std, variance, mode\n");
        printf("  * Funções Financeiras     - pv, fv, pmt, npv, irr, si, ci\n");
        printf("  * Funções de Configuração - setdec\n");
        printf("  * Aliases Português       - raiz, sen, media, mediana, vpl, tir\n");
    } else {
        printf("  * Basic Math              - +, -, *, /, %%, ^, !\n");
        printf("  * Math Functions          - sqrt, sin, cos, log, exp, abs\n");
        printf("  * Statistical Functions   - mean, median, std, variance, mode\n");
        printf("  * Financial Functions     - pv, fv, pmt, npv, irr, si, ci\n");
        printf("  * Configuration Functions - setdec\n");
        printf("  * Portuguese Aliases      - raiz, sen, media, mediana, vpl, tir\n");
    }
    
    printf("\n" BOLD "%s\n" RESET, get_help_examples_title());
    
    if (current_lang == LANG_PT) {
        printf("  > 5 + 3 * 2\n");
        printf("  > x = 10\n");
        printf("  > sqrt(x) + 2^3\n");
        printf("  > mean(1, 2, 3, 4, 5)\n");
        printf("  > pv(0.05, 10, 100)\n");
        printf("  > media(10, 20, 30)\n");
    } else {
        printf("  > 5 + 3 * 2\n");
        printf("  > x = 10\n");
        printf("  > sqrt(x) + 2^3\n");
        printf("  > mean(1, 2, 3, 4, 5)\n");
        printf("  > pv(0.05, 10, 100)\n");
        printf("  > media(10, 20, 30)\n");
    }
    
    printf("%s\n", get_help_more_help());
}

void print_function_help(const char* function_name) {
    print_help_header();
    printf("\n");
    
    // MATEMÁTICAS BÁSICAS
    if (strcmp(function_name, "+") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_add());
    }
    else if (strcmp(function_name, "-") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_sub());
    }
    else if (strcmp(function_name, "*") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_mul());
    }
    else if (strcmp(function_name, "/") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_div());
    }
    else if (strcmp(function_name, "%") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_mod());
    }
    else if (strcmp(function_name, "^") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_pow());
    }
    else if (strcmp(function_name, "!") == 0) {
        printf(BOLD "%s\n" RESET, get_help_operator_fact());
    }
    
    // FUNÇÕES MATEMÁTICAS
    else if (strcmp(function_name, "sqrt") == 0 || strcmp(function_name, "raiz") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_sqrt());
    }
    else if (strcmp(function_name, "sin") == 0 || strcmp(function_name, "sen") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_sin());
    }
    else if (strcmp(function_name, "cos") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_cos());
    }
    else if (strcmp(function_name, "tan") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_tan());
    }
    else if (strcmp(function_name, "log") == 0 || strcmp(function_name, "log10") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_log());
    }
    else if (strcmp(function_name, "ln") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_ln());
    }
    else if (strcmp(function_name, "exp") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_exp());
    }
    else if (strcmp(function_name, "abs") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_abs());
    }
    
    // FUNÇÕES ESTATÍSTICAS
    else if (strcmp(function_name, "mean") == 0 || strcmp(function_name, "media") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_mean());
    }
    else if (strcmp(function_name, "median") == 0 || strcmp(function_name, "mediana") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_median());
    }
    else if (strcmp(function_name, "std") == 0 || strcmp(function_name, "desvio") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_std());
    }
    else if (strcmp(function_name, "variance") == 0 || strcmp(function_name, "variancia") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_variance());
    }
    else if (strcmp(function_name, "mode") == 0 || strcmp(function_name, "moda") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_mode());
    }
    else if (strcmp(function_name, "sum") == 0 || strcmp(function_name, "soma") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_sum());
    }
    else if (strcmp(function_name, "min") == 0 || strcmp(function_name, "minimo") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_min());
    }
    else if (strcmp(function_name, "max") == 0 || strcmp(function_name, "maximo") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_max());
    }
    
    // FUNÇÕES FINANCEIRAS BÁSICAS
    else if (strcmp(function_name, "si") == 0 || strcmp(function_name, "js") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_si());
    }
    else if (strcmp(function_name, "fv_si") == 0 || strcmp(function_name, "montante_js") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_fv_si());
    }
    else if (strcmp(function_name, "ci") == 0 || strcmp(function_name, "jc") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_ci());
    }
    else if (strcmp(function_name, "fv_ci") == 0 || strcmp(function_name, "montante_jc") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_fv_ci());
    }
    
    // FUNÇÕES FINANCEIRAS AVANÇADAS
    else if (strcmp(function_name, "pv") == 0 || strcmp(function_name, "vp") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_pv());
    }
    else if (strcmp(function_name, "fv") == 0 || strcmp(function_name, "vf") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_fv());
    }
    else if (strcmp(function_name, "pmt") == 0 || strcmp(function_name, "pagamento") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_pmt());
    }
    else if (strcmp(function_name, "nper") == 0 || strcmp(function_name, "periodos") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_nper());
    }
    else if (strcmp(function_name, "rate") == 0 || strcmp(function_name, "taxa") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_rate());
    }
    else if (strcmp(function_name, "npv") == 0 || strcmp(function_name, "vpl") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_npv());
    }
    else if (strcmp(function_name, "irr") == 0 || strcmp(function_name, "tir") == 0) {
        printf(BOLD "%s\n" RESET, get_help_function_irr());
    }

    // FUNÇÕES FINANCEIRAS AVANÇADAS
    else if (strcmp(function_name, "setdec") == 0){
        printf(BOLD "%s\n" RESET, get_help_function_setdec());
    }    
    
    else {
        printf(ERROR_COLOR "%s\n" RESET, get_help_function_not_found(function_name));
    }
}


int get_total_help_pages() {
    return 4;
}

void print_help_page(int page) {
    print_help_header();
    
    if (current_lang == LANG_PT) {
        printf("\n" BOLD "Página %d de %d\n\n" RESET, page, get_total_help_pages());
    } else {
        printf("\n" BOLD "Page %d of %d\n\n" RESET, page, get_total_help_pages());
    }
    
    switch (page) {
        case 1:
            if (current_lang == LANG_PT) {
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
                printf(BOLD "cos" RESET "           Cosseno (radianos\n");
                printf(BOLD "tan" RESET "           Tangente (radianos)\n");
                printf(BOLD "log, log10" RESET "    Logaritmo base 10\n");
                printf(BOLD "ln" RESET "            Logaritmo natural\n");
                printf(BOLD "exp" RESET "           Exponencial (e^x)\n");
                printf(BOLD "abs" RESET "           Valor absoluto\n");
            } else {
                printf(BOLD "=== MATHEMATICAL OPERATORS ===\n\n" RESET);
                printf(BOLD "+" RESET "     Addition: a + b\n");
                printf(BOLD "-" RESET "     Subtraction: a - b\n");
                printf(BOLD "*" RESET "     Multiplication: a * b\n");
                printf(BOLD "/" RESET "     Division: a / b\n");
                printf(BOLD "%%" RESET "     Modulo: a %% b (division remainder)\n");
                printf(BOLD "^" RESET "     Power: a ^ b\n");
                printf(BOLD "!" RESET "     Factorial: a! (non-negative integers)\n");
                
                printf("\n" BOLD "=== MATHEMATICAL FUNCTIONS ===\n\n" RESET);
                printf(BOLD "sqrt, raiz" RESET "    Square root\n");
                printf(BOLD "sin, sen" RESET "      Sine (radians)\n");
                printf(BOLD "cos" RESET "           Cosine (radians)\n");
                printf(BOLD "tan" RESET "           Tangent (radians)\n");
                printf(BOLD "log, log10" RESET "    Base 10 logarithm\n");
                printf(BOLD "ln" RESET "            Natural logarithm\n");
                printf(BOLD "exp" RESET "           Exponential (e^x)\n");
                printf(BOLD "abs" RESET "           Absolute value\n");
            }
            break;
            
        case 2:
            if (current_lang == LANG_PT) {
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
            } else {
                printf(BOLD "=== STATISTICAL FUNCTIONS ===\n\n" RESET);
                printf(BOLD "mean, media" RESET "       Arithmetic mean\n");
                printf(BOLD "median, mediana" RESET "   Median\n");
                printf(BOLD "std, desvio" RESET "       Standard deviation\n");
                printf(BOLD "variance, variancia" RESET " Variance\n");
                printf(BOLD "mode, moda" RESET "        Mode (most frequent value)\n");
                printf(BOLD "sum, soma" RESET "         Total sum\n");
                printf(BOLD "min, minimo" RESET "       Minimum value\n");
                printf(BOLD "max, maximo" RESET "       Maximum value\n");
                
                printf("\n" BOLD "=== BASIC FINANCIAL FUNCTIONS ===\n\n" RESET);
                printf(BOLD "si, js" RESET "              Simple interest\n");
                printf(BOLD "fv_si, montante_js" RESET "  Simple interest amount\n");
                printf(BOLD "ci, jc" RESET "              Compound interest\n");
                printf(BOLD "fv_ci, montante_jc" RESET "  Compound interest amount\n");
            }
            break;
            
        case 3:
            if (current_lang == LANG_PT) {
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
            } else {
                printf(BOLD "=== ADVANCED FINANCIAL FUNCTIONS ===\n\n" RESET);
                printf(BOLD "pv, vp" RESET "           Present value\n");
                printf(BOLD "fv, vf" RESET "           Future value\n");
                printf(BOLD "pmt, pagamento" RESET "   Periodic payment\n");
                printf(BOLD "nper, periodos" RESET "   Number of periods\n");
                printf(BOLD "rate, taxa" RESET "       Interest rate\n");
                printf(BOLD "npv, vpl" RESET "         Net present value\n");
                printf(BOLD "irr, tir" RESET "         Internal rate of return\n");
                
                printf("\n" BOLD "=== PRACTICAL USAGE ===\n\n" RESET);
                printf("For detailed function help:\n");
                printf("  " BOLD "help sqrt" RESET "     - Shows help for sqrt function\n");
                printf("  " BOLD "help media" RESET "    - Shows help for mean function\n");
                printf("  " BOLD "help vpl" RESET "      - Shows help for npv function\n");
            }
            break;
        case 4:
            if (current_lang == LANG_PT) {
                printf(BOLD "=== FUNÇÕES DE CONFIGURAÇÃO ===\n\n" RESET);
                printf(BOLD "setdec" RESET "           Configura o número de casas decimais\n"); 
                printf("\n" BOLD "=== USO PRÁTICO ===\n\n" RESET);
                printf("  " BOLD "setdec(2)" RESET "     - Configura para os números exibirem 2 casas decimaist\n");
            } else {
                printf(BOLD "=== CONFIGURATION FUNCTIONS ===\n\n" RESET);
                printf(BOLD "setdec" RESET "           Sets the number of decimal places\n"); 
                printf("\n" BOLD "=== PRACTICAL USAGE ===\n\n" RESET);
                printf("  " BOLD "setdec(2)" RESET "     - Configures numbers to display 2 decimal places\n");
            }       
            break;
        default:
            printf(ERROR_COLOR "%s\n" RESET, get_help_invalid_page(page, get_total_help_pages()));
            return;
    }
    
    printf(CYAN "%s\n" RESET, get_help_page_navigation());
}
